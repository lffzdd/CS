#include"csapp.h"

void handler(int);
void initjobs();
void addjob(pid_t pid);
void deletejob(pid_t pid);

int main(int argc, char const* argv[]) {
  int pid;
  sigset_t mask_all, prev_mask;

  sigfillset(&mask_all);
  Signal(SIGCHLD, handler);
  initjobs();

  while (1) {
    if ((pid = Fork()) == 0) {
      Execve("/bin/date", NULL, NULL);
    }
    sigprocmask(SIG_BLOCK, &mask_all, &prev_mask); // 父进程阻塞所有信号
    addjob(pid);
    sigprocmask(SIG_SETMASK, &prev_mask, NULL); // 父进程解除阻塞

  }
  exit(0);
}

int main_(){
  int pid;
  sigset_t mask_all, mask_one, prev_one;

  sigfillset(&mask_all);
  sigemptyset(&mask_one);
  sigaddset(&mask_one, SIGCHLD);
  Signal(SIGCHLD, handler);
  initjobs();

  while (1) {
    sigprocmask(SIG_BLOCK, &mask_one, &prev_one); // 阻塞SIGCHLD信号
    if ((pid = Fork()) == 0) {
      sigprocmask(SIG_SETMASK, &prev_one, NULL); // 子进程会继承父进程的信号屏蔽字,而父进程已经阻塞了SIGCHLD信号,如果子进程需要创建新的进程,那么子进程需要解除对SIGCHLD信号的阻塞
      Execve("/bin/date", NULL, NULL);
    }
    sigprocmask(SIG_BLOCK, &mask_all, NULL);  // 父进程阻塞所有信号
    addjob(pid);
    sigprocmask(SIG_SETMASK, &prev_one, NULL); // 父进程解锁SIGCHLD信号
  }
  exit(0); 
}

void handler(int sig) {
  int olderrno = errno;
  sigset_t mask_all, prev_mask;
  pid_t pid;

  sigfillset(&mask_all);

  while ((pid = waitpid(-1, NULL, 0)) > 0) {
    sigprocmask( SIG_BLOCK, &mask_all, &prev_mask);
    deletejob(pid);
    sigprocmask(SIG_SETMASK, &prev_mask, NULL);
  }
  if (errno != ECHILD) {
    perror("waitpid error");
  }
  errno = olderrno;
}

void initjobs() {
  // 初始化作业列表
}

void addjob(pid_t pid) {
  // 添加作业到作业列表
}

void deletejob(pid_t pid) {
  // 从作业列表中删除作业
}