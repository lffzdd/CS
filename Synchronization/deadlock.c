#include"../code/src/csapp.c"
void* thread(void* vargp);
sem_t mutex[2];
int cnt = 0;
int main(int argc, char const* argv[]) {
    pthread_t tid1, tid2;
    sem_init(&mutex[0], 0, 1);
    sem_init(&mutex[1], 0, 1);
    pthread_create(&tid1, NULL, thread, (void*)0);
    pthread_create(&tid1, NULL, thread, (void*)1);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("cnt = %d\n", cnt);
    return 0;
}

void* thread(void* vargp) {
    int myid = *((int*)vargp);
    for (int i = 0; i < 10; i++) {
        sem_wait(&mutex[myid]);
        cnt++;
        sem_wait(&mutex[1 - myid]);
        sem_post(&mutex[myid]);

        sem_post(&mutex[1 - myid]);
    }
    return NULL;
}