#define _XOPEN_SOURCE 600
#include"../code/src/csapp.c"

void doit(int fd);
void readRequestBlank(rio_t*);
void clientError(int fd, char* cause, char* errnum, char* shortmsg, char* longmsg);
int parseUri(char* uri, char* filename, char* cgiArgs);
void serverStaticResponse(int fd, char* filename, int filesize);
void serverDynamicResponse(int fd, char* filename, char* cgiArgs);
void get_filetype(const char* filename, char*);
void getFiletype(char* filename, char* filetype, int bufsize);


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    // 定义存放客户端信息的变量
    int connfd;
    socklen_t clientlen;
    char hostname[MAXLINE], port[MAXLINE];
    struct sockaddr_storage clientaddr;

    int listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen);
        Getnameinfo((SA*)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("接受了来自 %s:%s 的连接\n", hostname, port);
        doit(connfd);
        Close(connfd);
    }


    return 0;
}

void doit(int fd) {
    rio_t rio;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);

    printf("请求头:\n");
    printf("%s", buf);

    sscanf(buf, "%s %s %s", method, uri, version);// GET / HTTP/1.1

    if (strcmp(method, "GET")) {
        clientError(fd, method, "501", "没有实现", "Tiny 没有实现该方法");
        return;
    }

    readRequestBlank(&rio);

    char filename[MAXLINE], cgiArgs[MAXLINE];
    int isStatic = parseUri(uri, filename, cgiArgs); // 1 为静态,0为动态

    struct stat statBuf;
    if (stat(filename, &statBuf) < 0) {
        clientError(fd, filename, "404", "Not found", "没有找到您请求的文件!");
        return;
    }

    if (isStatic) { // 静态请求
        if (!(S_ISREG(statBuf.st_mode)) || !(S_IRUSR & statBuf.st_mode)) {  // 检测是否为普通文件,以及用户读权限,S_IRUSR是权限位掩码
            clientError(fd, filename, "403", "Forbidden", "没有读权限");
            return;
        }
        serverStaticResponse(fd, filename, statBuf.st_size);
    }
    else {  // 动态请求
        if (!(S_ISREG(statBuf.st_mode)) || !(S_IXUSR & statBuf.st_mode)) {  // 检测是否为普通文件,以及用户执行权限
            clientError(fd, filename, "403", "Forbidden", "没有执行权限");
            return;
        }
        serverDynamicResponse(fd, filename, cgiArgs);
    }

}

void clientError(int fd, char* cause, char* errnum, char* shortmsg, char* longmsg) {
    char header[MAXLINE], body[MAXLINE];

    /* 构建响应体 */
    sprintf(body, "<html><title>Tiny 程序错误</title>\r\n");
    sprintf(body + strlen(body), "<body bgcolor=""ffffff"">\r\n");
    sprintf(body + strlen(body), "%s: %s\r\n", errnum, shortmsg);
    sprintf(body + strlen(body), "<p>%s: %s\r\n", longmsg, cause);
    sprintf(body + strlen(body), "<hr><em>The Tiny Web server</em>\r\n");

    /* 打印响应 */
    sprintf(header, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    sprintf(header + strlen(header), "Content-type: text/html\r\n");
    sprintf(header + strlen(header), "Content-length: %d\r\n\r\n", (int)strlen(body));

    Rio_writen(fd, header, strlen(header));
    Rio_writen(fd, body, strlen(body));
}


void readRequestBlank(rio_t* rio) {
    char buf[MAXLINE];
    Rio_readlineb(rio, buf, MAXLINE);
    while (strcmp(buf, "\r\n")) {
        Rio_readlineb(rio, buf, MAXLINE);
        printf("%s", buf);
    }
    return;
}

int parseUri(char* uri, char* filename, char* cgiArgs) {
    if (!strstr(uri, "cgi-bin")) {  // 返回 NULL,是静态资源
        strcpy(cgiArgs, "");
        strcpy(filename, ".");
        strcat(filename, uri);
        if (uri[strlen(uri) - 1] == '/') {
            strcat(filename, "index.html");
        }
        return 1;
    }
    else {  // 动态资源
        char* start = strstr(uri, "?");
        if (start) {
            char* end = strstr(start, " ");
            strncpy(cgiArgs, uri + 1, end - start - 1); // 要忽略"?"
        }
        else {
            strcpy(cgiArgs, "");
        }

        strcpy(filename, ".");
        strcat(filename, uri);
        return 0;

    }
}

void serverStaticResponse(int fd, char* filename, int filesize) {
    char header[MAXLINE];
    char filetype[1024];

    getFiletype(filename, filetype, 1024);

    sprintf(header, "HTTP/1.0 200 OK\r\n");
    sprintf(header + strlen(header), "Server: Tiny Web Server\r\n");
    sprintf(header + strlen(header), "Connection: close\r\n");
    sprintf(header + strlen(header), "Content-length: %d\r\n", filesize);
    sprintf(header + strlen(header), "Content-type: %s; charset=utf-8\r\n\r\n", filetype);

    Rio_writen(fd, header, strlen(header));
    printf("Response headers:\n");
    printf("%s", header);

    int srcfd = Open(filename, O_RDONLY, 0);
    char* srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize);
}

void getFiletype(char* filename, char* filetype, int bufsize) {
    // 后缀到MIME类型的映射表 
    const struct {
        const char* ext;
        const char* mime;
    } TYPE_MAP[] = {
        { "html", "text/html" },
        { "txt",  "text/plain" },
        { "gif",  "image/gif" },
        { "png",  "image/png" },
        { "jpg",  "image/jpeg" },
        { NULL,   "application/octet-stream" }  // 默认类型 
    };

    // 1. 查找最后一个点 
    const char* dot = strrchr(filename, '.');
    if (!dot || dot == filename) {  // 无后缀或隐藏文件（如 ".gitignore"）
        snprintf(filetype, bufsize, "%s", TYPE_MAP[5].mime);  // 使用默认类型 
        return;
    }

    // 2. 提取小写后缀（避免大小写敏感问题）
    char ext[16];
    const char* src = dot + 1;
    char* dst = ext;
    while (*src && dst - ext < 15) {
        *dst++ = tolower(*src++);
    }
    *dst = '\0';

    // 3. 匹配MIME类型
    for (int i = 0; TYPE_MAP[i].ext; i++) {
        if (strcmp(ext, TYPE_MAP[i].ext) == 0) {
            snprintf(filetype, bufsize, "%s", TYPE_MAP[i].mime);
            return;
        }
    }
    snprintf(filetype, bufsize, "%s", TYPE_MAP[5].mime);  // 未匹配则返回默认类型 
}

void get_filetype(const char* filename, char* filetype) {
    if (strstr(filename, ".html"))
        strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
        strcpy(filetype, "image/gif");
    else if (strstr(filename, ".png"))
        strcpy(filetype, "image/png");
    else if (strstr(filename, ".jpg"))
        strcpy(filetype, "image/jpeg");
    else
        strcpy(filetype, "text/plain");
}

void serverDynamicResponse(int fd, char* filename, char* cgiArgs) {
    char header[MAXLINE];

    sprintf(header, "HTTP/1.0 200 OK\r\n");
    sprintf(header + strlen(header), "Server: Tiny Web Server\r\n");
    sprintf(header + strlen(header), "Connection: close\r\n");
    Rio_writen(fd, header, strlen(header));

    if (Fork() == 0) {
        setenv("QUERY_STRING", cgiArgs, 1);
        Dup2(fd, STDOUT_FILENO); // 把标准输出重定向到fd
        Execve(filename, (char* []) { filename, NULL }, environ);
    }
    Wait(NULL);

}