#include "../code/src/csapp.c"
/*
读可以并行
写是互斥的
如果有多个读,导致写一直阻塞,则会导致饥饿
*/
int readcount = 0; // 读者数量
sem_t w,mutex;
void writer(void) {
    while (1) {
        sem_wait(&w);

        printf("Writing...\n");
        sleep(1);

        sem_post(&w);
    }
}

void reader(void) {
    while (1) {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1) {
            sem_wait(&w);
        }
        sem_post(&mutex);

        printf("Reading...\n");
        sleep(1);

        sem_wait(&mutex);
        readcount--;
        if (readcount == 0) {
            sem_post(&w);
        }
        sem_post(&mutex);
    }
}