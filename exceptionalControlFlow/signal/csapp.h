#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<wait.h>
#include<unistd.h>
#include<errno.h>

#ifndef __USE_POSIX
#define __USE_POSIX
#endif

#include<signal.h>

pid_t Fork(void) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(0);
  }
  printf("\t\t\t\tFork()=>pid:%d\n", pid);
  return pid;
}

void Kill(pid_t pid, int signum) {
  if (kill(pid, signum) < 0) { //kill()函数向进程发送信号,成功返回0,失败返回-1,kill位于signal.h头文件中
    perror("kill");
    exit(0);
  }
}

__sighandler_t Signal(int sig, __sighandler_t handler) {
  __sighandler_t ret;
  if ((ret = signal(sig, handler)) == SIG_ERR) {
    perror("signal error");
    exit(0);
  }

  return ret;
}