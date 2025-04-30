#include"csapp.h"

int main(int argc, char const* argv[]) {
  pid_t pid;

  if ((pid = Fork()) == 0) {
    printf("child started\n");
    fflush(fileout);
    pause(); // pause()函数使调用进程挂起直到有信号递达
    printf("control should never reach here!\nit should be terminated by a signal\n");
    exit(0);
  }

  printf("parent started, child pid = %d\n", pid);
  sleep(1);
  Kill(pid, SIGKILL);
  exit(0);

}


