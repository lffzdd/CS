#include "csapp.h"

#define N 5

int ccount = 0;

void child_handler(int);
void child_handler2(int);

int main(int argc, char const* argv[]) {
  __pid_t pid[N];
  ccount = N;
  // Signal(SIGCHLD, child_handler);
  Signal(SIGCHLD, child_handler2);

  for (int i = 0; i < N; i++) {
    if ((pid[i] = Fork()) == 0) {
      printf("Hello from child %d\n", i);
      sleep(1);
      exit(0);
    }
  }

  while (ccount > 0);
  printf("All children have terminated\n");

  return 0;
}

void child_handler(int sig) {
  int olderrno = errno; // errorno是一个全局变量,保存了最近一次的错误代码,位于errno.h头文件中
  __pid_t pid;
  if ((pid = waitpid(-1, NULL, 0)) < 0) {
    perror("waitpid error"); // unix_error()函数位于csapp.h头文件中,用来打印错误信息,和perror()函数类似
  }

  ccount--;
  printf("Handler reaped child %d\n", pid);
  sleep(1);

  errno = olderrno;
}

void child_handler2(int sig) {
  int olderrno = errno;
  __pid_t pid;
  while ((pid = waitpid(-1, NULL, 0)) > 0) {
    ccount--;
    printf("Handler reaped child %d\n", pid);
    sleep(1);
  }

  if (errno != ECHILD) { // ECHILD表示没有子进程
    perror("waitpid error");
  }

  errno = olderrno;
}