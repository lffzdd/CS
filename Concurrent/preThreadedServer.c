#include"../code/src/csapp.c"
#include"../code/conc/sbuf.c"

void* thread(void* vargp); // 线程函数

sbuf_t sbuf; // 定义一个sbuf_t类型的变量sbuf

int main(int argc, char* argv[]) {
    int i, listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; // Enough space for any address
    pthread_t tid;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    listenfd = Open_listenfd(argv[1]);
    sbuf_init(&sbuf, 16); // 初始化sbuf, 16个槽位

    for (i = 0; i < 8; i++) { // 创建8个线程
        Pthread_create(&tid, NULL, thread, NULL);
    }
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen); // 接受连接
        sbuf_insert(&sbuf, connfd); // 将连接插入到sbuf中
    }
    return 0;
}

static void init_echo_client(); // 初始化函数
void echo_client(int connfd);

void* thread(void* vargp) {
    Pthread_detach(pthread_self()); // 分离线程
    while (1) {
        int connfd = sbuf_remove(&sbuf); // 从sbuf中取出连接
        echo_client(connfd); // 处理连接
        Close(connfd); // 关闭连接
    }
}

static int byte_cnt; // 统计字节数
static sem_t mutex; // 互斥锁

static void init_echo_client() {
    Sem_init(&mutex, 0, 1); // 初始化互斥锁
    byte_cnt = 0; // 初始化字节数
}

void echo_client(int connfd) {
    char buf[MAXLINE];
    rio_t rio;
    int n;
    static pthread_once_t once = PTHREAD_ONCE_INIT; // 线程一次初始化

    Pthread_once(&once, init_echo_client); // 线程一次初始化
    Rio_readinitb(&rio, connfd); // 初始化rio
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { // 读取一行
        if (strncmp(buf, "exit", 4) == 0 && (buf[4] == '\n' || buf[4] == '\r')) { // 如果是exit开头并紧跟换行,则退出
            printf("thread %d exit\n", (int)pthread_self());
            break;
        }

        P(&mutex); // 上锁
        byte_cnt += n; // 统计字节数
        printf("thread %d received %d (%d total) bytes on fd %d\n", (int)pthread_self(), n, byte_cnt, connfd);
        V(&mutex); // 解锁
        Rio_writen(connfd, buf, n); // 回显
    }
}
