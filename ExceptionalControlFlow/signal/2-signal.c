#include <stdio.h>
#include <signal.h>
#include <unistd.h> // unistd是UNIX标准的一部分,包含了许多UNIX系统服务的函数原型
#include <stdlib.h>

void handler(int sig) {
  printf("Signal received: %d\n", sig);
  exit(0);
}

int main() {
  if (signal(SIGINT, handler) == SIG_ERR) {
    perror("signal");
    exit(0);
  }  // 注册 SIGINT 信号处理函数
  
  while (1) {
    printf("Running...\n");
    sleep(1);
  }
  return 0;
}