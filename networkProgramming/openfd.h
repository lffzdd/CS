#define _XOPEN_SOURCE 600
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<errno.h>

int OpenClientFd(char* hostname, char* port);
int OpenListenFd(char* port);

int openClentFd(char* hostname, char* port) {
    struct addrinfo hints, * AIList;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;

    int rc;
    if ((rc = getaddrinfo(hostname, port, &hints, &AIList)) != 0) {
        fprintf(stderr, "getaddrinfo 失败 (%s:%s):%s\n", hostname, port, gai_strerror(rc));
        return -2;
    }

    struct addrinfo* addr;
    int clientfd;
    for (addr = AIList; addr; addr = addr->ai_next) {
        // 获取套接字
        if ((clientfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) < 0) {
            continue;
        }

        if ((connect(clientfd, addr->ai_addr, addr->ai_addrlen)) != -1) {
            break;
        }

        if (close(clientfd) < 0) {
            fprintf(stderr, "关闭 clientfd 错误:%s\n", strerror(errno));
            return -1;
        }
    }

    freeaddrinfo(AIList);
    if (!addr) { // addr 遍历到了最后
        return -1;
    }

    return clientfd;
}

int openLsitenFd(char* port) {
    struct addrinfo hints, * AIList;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;

    int rc;
    if ((rc = getaddrinfo(NULL, port, &hints, &AIList)) != 0) {
        fprintf(stderr, "getaddrinfo 失败 (port %s):%s\n", port, gai_strerror(rc));
        return -2;
    }

    struct addrinfo* addr;
    int listenfd, optval = 1;
    for (addr = AIList; addr; addr = addr->ai_next) {
        // 获取套接字
        if ((listenfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) < 0) {
            continue;
        }

        if ((connect(listenfd, addr->ai_addr, addr->ai_addrlen)) != -1) {
            break;
        }

        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int)); // 告诉内核允许该套接字重用本地地址和端口。

        if (bind(listenfd, addr->ai_addr, addr->ai_addrlen) < 0) {
            fprintf(stderr, "bind clientfd 错误:%s\n", strerror(errno));
            return -1;
        }
        if (close(listenfd) < 0) {
            fprintf(stderr, "关闭 listenfd 错误:%s\n", strerror(errno));
            return -1;
        }

    }

    freeaddrinfo(AIList);
    if (!addr) { // addr 遍历到了最后
        return -1;
    }
    if (listen(listenfd, 1024) < 0) { // 可以同时排队 1024 个等待建立的连接。
        close(listenfd);
        return -1;
    }


    return listenfd;
}

int OpenClientFd(char* hostname, char* port) {
    int rc;

    if ((rc = openClentFd(hostname, port)) < 0) {
        fprintf(stderr, "OpenClientFd 错误:%s\n", strerror(errno));
        return -1;
    }
    return rc;
}

int OpenListenFd(char* port) {
    int rc;

    if ((rc = openLsitenFd(port)) < 0) {
        fprintf(stderr, "OpenListenFd 错误:%s\n", strerror(errno));
        return -1;
    }
    return rc;
}