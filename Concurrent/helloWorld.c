#include"../code/src/csapp.c"

void* thread(void* vargp);

int main(int argc, char const* argv[]) {
    pthread_t tid;
    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL); // 等待线程结束
    return 0;
}

void* thread(void* vargp) {
    printf("Hello, World!\n");
    return NULL;
}
