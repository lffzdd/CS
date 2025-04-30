#include"../code/src/csapp.c"

void* thread(void* vargp); // 线程函数
void echo(int connfd);

int main(int argc, char * argv[]) {
    int listenfd, * connfdp;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char hostname[MAXLINE], port[MAXLINE];
    pthread_t tid;

    listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfdp = Malloc(sizeof(int)); // 分配内存
        *connfdp = Accept(listenfd, (SA*)&clientaddr, &clientlen); // 接受连接
        Getnameinfo((SA*)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0); // 获取主机名和端口号
        printf("接受了来自 %s:%s 的连接\n", hostname, port);
        Pthread_create(&tid, NULL, thread, connfdp); // 创建线程
    }
    // 这里的connfdp是一个指针,在创建线程时传递给线程函数
    // 如果是传递&connfd,而不是connfd

    return 0;
}

void* thread(void* vargp) {
    int connfd = *((int*)vargp); // 获取连接套接字
    Free(vargp); // 释放内存
    Pthread_detach(pthread_self()); // 分离线程
    echo(connfd); // 处理请求
    Close(connfd); // 关闭连接套接字
    return NULL;
}

/**
 * 返回客户端发送的数据
 * 
 * @param connfd:一个连接的套接字
 */
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

