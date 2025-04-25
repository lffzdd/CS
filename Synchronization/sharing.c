#include"../code/src/csapp.c"

void* thread(void* vargp);

char** ptr;

int main(int argc, char const* argv[]) {
    long i;
    pthread_t tid;
    char* msgs[2] = {
        "Hello from thread 1",
        "Hello from thread 2"
    };

    ptr = msgs;
    for (i = 0; i < 2; i++) {
        Pthread_create(
            &tid, NULL, thread, (void*)i
        );
    }
    Pthread_exit(NULL);
}

void* thread(void* vargp) {
    long myid = (long)vargp;
    static int cnt = 0;
    printf("[%ld]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
    return NULL;
}