#include"../code/src/csapp.c"

void* thread(void* vargp);
volatile long cnt = 0; // volatile 告诉编译器永远不要把该变量放在寄存器中,volatile 修饰的变量总是从内存中读取,修改后又写回内存中,而不是放在寄存器中,这样可以避免编译器优化导致的错误
// 一些局部变量在编译器优化时会被放在寄存器中,而不会放到栈中,volatile 阻止了这种优化,这样可以避免编译器优化导致的错误

int main(int argc, char const* argv[]) {
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
        cnt++;
    }
    return NULL;
}
