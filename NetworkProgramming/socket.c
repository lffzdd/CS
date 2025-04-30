#include"code/include/csapp.h"

int main(int argc, char const* argv[]) {
    struct sockaddr clientaddr;
    /* sockaddr - 通用套接字地址结构
    sa_family_t sa_family; // 地址族,指定了套接字的类型,比如AF_INET是IPv4,AF_INET6是IPv6,
    PFSOCK_STREAM是TCP,SOCK_DGRAM是UDP
    char sa_data[14]; // 地址数据
    */

    struct sockaddr_in ipv4;
    /* sockaddr_in - IPv4套接字地址结构
    sa_family_t sin_family; // 地址族,永远是AF_INET,2字节
    in_port_t sin_port; // 端口号,2字节
    struct in_addr sin_addr; // IPv4地址,4字节
    char sin_zero[8]; // 8字节填充,使sockaddr_in和sockaddr一样大
    */
    return 0;
}
