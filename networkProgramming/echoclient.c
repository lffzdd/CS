#define _XOPEN_SOURCE 600
#include"../code/src/csapp.c"

int main(int argc, char* argv[]) {
    int clientfd;
    char* host, * port, buf[MAXLINE];
    rio_t rio;
    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port); // 创建一个连接套接字
    Rio_readinitb(&rio, clientfd); // 初始化一个rio_t结构体,为connfd分配一个缓冲区

    while (Fgets(buf, MAXLINE, stdin) != NULL) { // 从标准输入中读取一行数据
        Rio_writen(clientfd, buf, strlen(buf)); // 将buf中的数据写入connfd中
        Rio_readlineb(&rio, buf, MAXLINE); // 从rio中读取一行数据,放入buf中
        Fputs(buf, stdout); // 将buf中的数据输出到标准输出中
    }
    Close(clientfd); // 关闭连接

    return 0;
}
