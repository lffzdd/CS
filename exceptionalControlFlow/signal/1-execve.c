#include <stdio.h>
#include <unistd.h>
#include <wait.h>

void execveExample() {
  int x = 1;
  pid_t pid;
  char* myargv[] = { "/bin/ls","-lt",NULL };
  char* myenv[] = { NULL };
  if ((pid = fork()) == 0) {
    printf("x:%d\n", x);

    int ret = execve(myargv[0], myargv, myenv);
    if (ret < 0) {
      printf("execve failed,%s: Command not found.\n", myargv[0]);
      perror("execve");
    }

    printf("x:%d\n", x); // execve()函数执行成功后,进程的内存空间会被新的程序覆盖,所以这里的x是无法访问的
  }

  else {
    wait(NULL);
    printf("Child process terminated\n");
    // execve("/bin/ls", "/bin/ls", NULL);
  }

}

int main() {

  execveExample();
  return 0;
}
