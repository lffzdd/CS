#include"code/include/csapp.h"

int main(int argc, char const* argv[]) {
    /* 建立网络连接流程
    1. getaddrinfo - 获取地址信息

    2. socket - 创建套接字
        使用socket()函数创建一个套接字,并返回一个文件描述符
        套接字是一个缓冲区,用于在网络上发送和接收数据,套接字是一个抽象的概念,在内核中实现,应用程序通过套接字接口与内核通信

    3. bind - 绑定套接字
        bind()函数是服务器上的一个特殊函数,在内核态中,创建一个接口,将套接字和一个特定的IP地址和端口号绑定在一起

    4. listen - 监听套接字
        listen()函数是服务器上的一个特殊函数,在内核态中,创建一个队列,用于存放客户端的连接请求,队列的长度由backlog参数指定.
        同时,将套接字和队列绑定在一起,并标记套接字为被动套接字,即服务器套接字,只能接受连接请求,不能主动发起连接请求

    5. accept - 接受连接
        服务器通过accept()函数接受客户端的连接请求,accept()函数会阻塞,直到有客户端连接请求到达,accept()函数返回一个新的套接字,用于和客户端通信
        accept()函数会从队列中取出一个连接请求,并将客户端的地址信息填充到clientaddr参数中

    第一个socket缓存来自客户端的连接请求,accept()使用这个socket处理请求,每成功处理一个客户端请求,会返回一个新的socket,这个新的socket用于后续和这个客户端通信
    一个串行服务器只能处理一个请求,只有当前socket关闭后,才能进行下一次的accept
    */
    int clientfd = Socket(AF_INET, SOCK_STREAM, 0); // AF_INET - IPv4, SOCK_STREAM - TCP, 0 - 协议编号,对于IPV4和SOCK_STREAM,自动选择IPPROTO_TCP,如果是SOCk_DGRAM,自动选择IPPROTO_UDP,自己手动指定的协议不匹配会报错
    return 0;
}
