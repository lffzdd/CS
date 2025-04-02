#define _XOPEN_SOURCE 600
#include"../code/src/csapp.c"

void sigchld_handler(int sig);
void echo(int);

int main(int argc, char * argv[]) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct  sockaddr_storage clientaddr;
    char hostname[MAXLINE], port[MAXLINE];

    Signal(SIGCHLD, sigchld_handler); // 注册 SIGCHLD 信号处理函数
    listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen);
        Getnameinfo((SA*)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("接受了来自 %s:%s 的连接\n", hostname, port);
        if (Fork() == 0) { // 子进程
            Close(listenfd); // 关闭监听套接字
            echo(connfd); // 处理请求
            Close(connfd); // 关闭连接套接字
            printf("关闭连接 %s:%s\n", hostname, port);
            exit(0); // 退出子进程
        }
        else { // 父进程
            Close(connfd); // 关闭连接套接字
        }

    }
    return 0;
}

void sigchld_handler(int sig) {
    int olderrno = errno;
    while (waitpid(-1, 0, WNOHANG) > 0); // 回收子进程
    errno = olderrno;
}

// connfd:一个连接的套接字
void echo(int connfd) {
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd); // 初始化一个rio_t结构体,为connfd分配一个缓冲区
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { // 从rio中读取一行数据,放入buf中
        printf("server received %d bytes\n", (int)n);
        printf("%s", buf); // 打印buf中的数据
        Rio_writen(connfd, buf, n); // 将buf中的数据写入connfd中
    }
}

