#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#ifndef __USE_POSIX
#define __USE_POSIX
#endif

#include<signal.h>

int sigprocmask(int how, const sigset_t* set, sigset_t* oldset);
/* 根据how参数的不同,可以实现不同的功能,如SIG_BLOCK, SIG_UNBLOCK, SIG_SETMASK, set参数是新的信号屏蔽字,
oldset参数是旧的信号屏蔽字,如果oldset不是NULL,则会把之前的BLOCK写入oldset中,

SIG_BLOCK是把set中的信号添加到当前的信号屏蔽字中,
SIG_UNBLOCK是把set中的信号从当前的信号屏蔽字中删除,
SIG_SETMASK是把当前的信号屏蔽字设置为set中的信号屏蔽字 */
int sigemptyset(sigset_t* set); // sigemptyset()函数用来初始化信号集,将set中的所有信号都清空
int sigfillset(sigset_t* set); // sigfillset()函数用来初始化信号集,将set中的所有信号都设置
int sigaddset(sigset_t* set, int signum); // sigaddset()函数用来向信号集中添加一个信号
int sigdelset(sigset_t* set, int signum); // sigdelset()函数用来从信号集中删除一个信号
int sigismember(const sigset_t* set, int signum); // sigismember()函数用来判断一个信号是否在信号集中
int sigsuspend(const sigset_t* set); // sigsuspend()函数用来挂起进程,直到有信号递达,然后恢复信号屏蔽字

void handler(int);
__sighandler_t Signal(int sig, __sighandler_t handler);

int main(int argc, char const* argv[]) {
  sigset_t mask, prev_mask;
  sigemptyset(&mask); // 初始化信号集
  sigaddset(&mask, SIGINT); // 添加SIGINT信号

  Signal(SIGINT, handler); // 注册SIGINT信号处理函数

  sigprocmask(SIG_BLOCK, &mask, &prev_mask);

  printf("SIGINT has been blocked\n");
  printf("Sleeping 5 seconds\n");
  sleep(5);

  sigprocmask(SIG_SETMASK, &prev_mask, NULL);
  printf("SIGINT has been unblocked\n");
  sleep(10);

  return 0;
}

__sighandler_t Signal(int sig, __sighandler_t handler) {
  __sighandler_t ret;
  if ((ret = signal(sig, handler)) == SIG_ERR) {
    perror("signal error");
    exit(0);
  }

  return ret;
}
void handler(int sig) {
  printf("Signal received: %d\n", sig);
}