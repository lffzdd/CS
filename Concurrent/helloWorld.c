#include"../code/src/csapp.c"

void* thread(void* vargp);

int main(int argc, char const* argv[]) {
    pthread_t tid;
    int arr[5] = {1, 2, 3, 4, 5};
    pthread_create(&tid, NULL, thread, arr);
    printf("新线程的ID是:%lu\n", tid);

    int *retval;
    Pthread_join(tid, (void**)&retval); // 等待线程结束
    printf("线程返回值是:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d \t", retval[i]);
    }
    printf("\n");
    return 0;
}

void* thread(void* vargp) {
    printf("我的线程ID是:%lu\n", pthread_self());
    printf("Hello, World!\n");

    int *arr = (int*)vargp;
    for (int i = 0; i < 5; i++) {
        printf("%d \t", arr[i]);
    }
    printf("\n");
    pthread_exit((void *)arr); // 线程退出
}
