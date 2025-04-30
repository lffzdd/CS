#define _XOPEN_SOURCE 600

#include"../code/src/csapp.c"

void echo(int connfd);

int main(int argc, char* argv[]) {
    int listenfd, connfd;
    socklen_t clientlen;

    listenfd = Open_listenfd(argv[1]); // 创建监听套接字

    fd_set read_set, ready_set;

    FD_ZERO(&read_set); // 清空集合
    FD_SET(STDIN_FILENO, &read_set); // 将标准输入加入集合
    FD_SET(listenfd, &read_set); // 将监听套接字加入集合

    while (1) {
        ready_set = read_set; // 复制集合
        int nready = Select(listenfd + 1, &ready_set, NULL, NULL, NULL); // 阻塞等待 
        if (FD_ISSET(STDIN_FILENO, &ready_set)) { // 如果标准输入有数据
            char buf[MAXLINE];
            int n = read(STDIN_FILENO, buf, MAXLINE); // 读取数据
            if (n > 0) {
                printf("stdin: %s", buf); // 打印数据
            }
        }

        char hostname[MAXLINE], port[MAXLINE];
        struct sockaddr_storage clientaddr;
        if (FD_ISSET(listenfd, &ready_set)) { // 如果监听套接字有数据
            clientlen = sizeof(struct sockaddr_storage);
            connfd = accept(listenfd, (SA*)&clientaddr, &clientlen); // 接受连接


            Getnameinfo((SA*)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0); // 获取客户端信息
            printf("接受了来自 %s:%s 的连接\n", hostname, port);

            echo(connfd); // 处理请求

            Close(connfd); // 关闭连接套接字
            printf("关闭连接 %s:%s\n", hostname, port);
        }

    }


    return 0;
}

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
