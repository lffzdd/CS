#include "../code/src/csapp.c"


typedef struct { /* Represents a pool of connected descriptors */
    int maxfd;   /* Largest descriptor in read_set */
    fd_set read_set; /* Set of all active descriptors */
    fd_set ready_set; /* Subset of descriptors ready for reading */
    int nready;  /* Number of ready descriptors from select */
    int maxi;   /* High water index into client array ,指的是当前连接的最大索引 */
    int clientfd[FD_SETSIZE]; /* Set of active descriptors */
    rio_t clientrio[FD_SETSIZE]; /* Set of active read buffers */
} pool;

void init_pool(int listenfd, pool* p);
void add_client(int connfd, pool* p);
void check_client(pool* p);

int byte_cnt = 0; /* Counts total bytes received by server */

int main(int argc, char** argv) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool; /* Set of connected descriptors */

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    listenfd = Open_listenfd(argv[1]); /* Create listening descriptor */
    init_pool(listenfd, &pool); /* Initialize the pool */

    while (1) {
        pool.ready_set = pool.read_set; /* Reset ready set */
        pool.nready = select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL); /* Wait for an event */

        if (FD_ISSET(listenfd, &pool.ready_set)) { /* New client connection */
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen); /* Accept connection */
            add_client(connfd, &pool); /* Add to the pool */

            char hostname[MAXLINE], port[MAXLINE];
            Getnameinfo((SA*)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0); /* Get client info */
            printf("Accepted connection from %s:%s\n", hostname, port);
        }
        check_client(&pool); /* Check for I/O on other descriptors */
    }
}

void init_pool(int listenfd, pool* p) {
    p->maxi = -1; /* Largest index in client array */
    for (int i = 0; i < FD_SETSIZE; i++) {
        p->clientfd[i] = -1; /* -1 indicates available entry */
    }
    p->maxfd = listenfd; /* Listenfd is the largest descriptor */
    p->clientfd[0] = listenfd; /* Add listenfd to the client array */
    FD_ZERO(&p->read_set); /* Clear all set bits */
    FD_SET(listenfd, &p->read_set); /* Add listenfd to the set */
}

void add_client(int connfd, pool* p) {
    int i;
    p->nready--; /* One less descriptor to process */
    for (i = 0; i < FD_SETSIZE; i++) {
        if (p->clientfd[i] < 0) {
            p->clientfd[i] = connfd; /* Add connected descriptor to the array */
            Rio_readinitb(&p->clientrio[i], connfd); /* Initialize buffer for client */

            FD_SET(connfd, &p->read_set); /* Add to the set */
            break;
        }
    }
    if (i == FD_SETSIZE) {
        app_error("add_client error: Too many clients");
    }
    if (connfd > p->maxfd) {
        p->maxfd = connfd; /* Update maxfd */
    }
    if (i > p->maxi) {
        p->maxi = i; /* Update maxi */
    }
    FD_SET(connfd, &p->read_set); /* Add to the set */
}

void check_client(pool* p) {
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for (i = 0; (i <= p->maxi) && (p->nready > 0);i++) {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        /* 如果描述符可读 */
        if ((FD_ISSET(connfd, &p->ready_set)) && (connfd > 0)) {
            p->nready--;
            if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
                byte_cnt += n; /* Update byte count */
                printf("server received %d (%d total) bytes on fd %d\n", n, byte_cnt, connfd);
                Rio_writen(connfd, buf, n);
            }
            else {
                Close(connfd);
                FD_CLR(connfd, &p->read_set); /* Remove from the set */
                p->clientfd[i] = -1;
            }
        }
    }

}
