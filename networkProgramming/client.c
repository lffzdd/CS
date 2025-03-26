#include"code/include/csapp.h"

int main(int argc, char const* argv[]) {
    /* 建立网络连接流程
    1. getaddrinfo - 获取地址信息

    2. socket - 创建套接字
        使用socket()函数创建一个套接字,并返回一个文件描述符
        套接字是一个缓冲区,用于在网络上发送和接收数据,套接字是一个抽象的概念,在内核中实现,应用程序通过套接字接口与内核通信

    3. connect - 连接套接字
        connect()函数是客户端上的函数,在内核态中,创建一个连接,将套接字和一个特定的IP地址和端口号绑定在一起,并向服务器发起连接请求
        connect()函数会阻塞,直到连接成功,或者出现错误,如果连接成功,connect()函数返回0,否则返回-1,并设置errno
    */
    int clientfd = Socket(AF_INET, SOCK_STREAM, 0); // AF_INET - IPv4, SOCK_STREAM - TCP, 0 - 协议编号,对于IPV4和SOCK_STREAM,自动选择IPPROTO_TCP,如果是SOCk_DGRAM,自动选择IPPROTO_UDP,自己手动指定的协议不匹配会报错
    return 0;
}
