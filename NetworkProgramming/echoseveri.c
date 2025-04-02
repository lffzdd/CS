#define _XOPEN_SOURCE 600
#include"../code/src/csapp.c"

void echo(int connfd);

int main(int argc, char* argv[]) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; // 用于存储客户端地址信息
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]); // 创建一个监听套接字
    while (1) {
        clientlen = sizeof(struct sockaddr_storage); // 初始化clientlen
        connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen); // 接受一个连接请求
        Getnameinfo((SA*)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0); // 获取客户端地址信息
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        echo(connfd); // 处理请求
        Close(connfd); // 关闭连接
    }
    return 0;
}

// connfd:一个连接的套接字
void echo(int connfd) {
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd); // 初始化一个rio_t结构体,为connfd分配一个缓冲区
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { // 从rio中读取一行数据,放入buf中
        printf("server received %d bytes\n", (int)n);
        Rio_writen(connfd, buf, n); // 将buf中的数据写入connfd中
    }
}
