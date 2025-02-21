#include"csapp.h"

void sigchld_handler(int);

void sigint_handler(int);

volatile sig_atomic_t pid;

int main(int argc, char const* argv[]) {
  sigset_t mask, prev;
  Signal(SIGCHLD, sigchld_handler);
  Signal(SIGINT, sigint_handler);
  sigemptyset(&mask);
  sigaddset(&mask, SIGCHLD);

  while (1) {
    sigprocmask(SIG_BLOCK, &mask, &prev); // 阻塞SIGCHLD信号
    if (Fork() == 0) {
      exit(0);
    }
    pid = 0;
    sigprocmask(SIG_SETMASK, &prev, NULL); // 解除阻塞

    // 等待SIGCHLD信号
    while (!pid) // 会一直等待,直到pid不为0,比较浪费资源
      // pause(); // 挂起进程,直到有信号递达,但是这里是先判断pid为0再调用pause()函数等待,如果在判断和调用pause()之间有信号递达,也就是判断pid等于0,然后信号传达,pid被赋值,然后pause()函数调用,这时候就会一直挂起,因为信号已经传达过来了,pause()可能等待不到信号
      sigsuspend(&prev); // 挂起进程,直到有信号递达,并且解除阻塞,
    /*  它相当于
    sigprocmask(SIG_BLOCK, &mask, &prev);
    pause();
    sigprocmask(SIG_SETMASK, &mask, NULL);
    这样pause()函数就不会有上面的问题了
    */

    exit(0);
  }

  void sigchld_handler(int sig) {
    int olderrno = errno;
    pid_t pid;
    pid = waitpid(-1, NULL, 0);

    errno = olderrno;
  }

  void sigint_handler(int sig) {
    int olderrno = errno;
    printf("Caught SIGINT\n");
    errno = olderrno;
  }