#define _XOPEN_SOURCE 600
// #include"code/include/csapp.h"
#include"code/src/csapp.c"

int main(int argc, char const* argv[]) {
    struct addrinfo *p, *listp, hints;
    char buf[MAXLINE];
    int rc, flags;
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    if ((rc=getaddrinfo(argv[1],NULL,&hints,&listp))!=0) {
        fprintf(stderr,"getaddrinfo failed (port %s): %s\n",argv[1],gai_strerror(rc));
        return 1;
    }

    return 0;
}
