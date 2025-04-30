#include"../code/src/csapp.c"

void* thread(void* vargp);
volatile long cnt = 0;
sem_t mutex; // 定义一个信号量

int main(int argc, char const* argv[]) {
    sem_init(&mutex, 0, 1); // 初始化信号量

    long niters;
    pthread_t tid1, tid2;

    niters = atoi(argv[1]);

    Pthread_create(&tid1, NULL, thread, (void*)niters);
    Pthread_create(&tid2, NULL, thread, (void*)niters);
    Pthread_join(tid1, NULL);
    Pthread_join(tid2, NULL);

    if (cnt != 2 * niters) {
        printf("BOOM! cnt=%ld\n", cnt);
    }
    else {
        printf("OK! cnt=%ld\n", cnt);
    }


    return 0;
}

void* thread(void* vargp) {
    long i, niters = (long)vargp;
    for (i = 0; i < niters; i++) {
        sem_wait(&mutex); // P操作
        cnt++;
        sem_post(&mutex); // V操作
    }
    return NULL;
}
