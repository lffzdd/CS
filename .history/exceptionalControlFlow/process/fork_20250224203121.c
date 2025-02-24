#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int fork1();
void fork2();
void fork3();
void fork4();
void fork5();
void fork6();
void fork7();
void fork8();
void execveExample();

int main(int argc, char* argv[]) {
  // fork1();
  // fork2();
  // fork3();
  // fork4(); // ZOMBIE
  // fork5();
  // fork6();
  // fork7();
  // fork8();
  execveExample();
  return EXIT_SUCCESS;
}

int fork1() {
  int x = 1;

  __pid_t subPid = fork(); // fork() is a system call,位于unistd.h,返回值是子进程的pid
  // 子进程与父进程的pid不同,它的内存上下文内容是父进程的副本
  // 函数会返回,从内存上看也就是执行中断返回,kernel会返回到继续执行的地方,但是fork()的中断返回可能会有两个地方,一个是父进程,一个是子进程,无法确定

  if (subPid == 0) {
    // 子进程
    printf("I am the child process, my pid is %d\n", ++x);
    printf("I am the child process, my pid is %d\n", getpid());
    exit(0);
  }
  else if (subPid > 0) {
    // 父进程
    printf("I am the parent process, my pid is %d\n", --x);
    printf("I am the parent process, my pid is %d\n", getpid());
    exit(0);
  }
  else {
    perror("fork");
    return EXIT_FAILURE;
  }
}

void fork2() {
  printf("L0\n");
  fork();
  printf("L1\n");
  fork();
  printf("Bye\n");
  for
}

void fork3() {
  printf("L0\n");
  if (fork() != 0) {
    printf("L1\n");
    if (fork() != 0) {
      printf("L2\n");
    }
  }
  printf("Bye\n");
}

void fork4() { // ZOMBIE
  if (fork() == 0) {
    printf("I am the child process, my pid is %d\n", getpid());
    sleep(30);
    exit(0);
  }
  else {
    printf("I am the parent process, my pid is %d\n", getpid());
    while (1) {
      sleep(1);
    }
  }
}

void fork5() {
  if (fork() == 0) {
    printf("I am the child process, my pid is %d\n", getpid());
    while (1) {
    }
  }
  else {
    printf("I am the parent process, my pid is %d\n", getpid());
    exit(0);
  }
}

void fork6() {
  int child_status;

  if (fork() == 0) {
    printf("I am the child process, my pid is %d\n", getpid());
    exit(0);
  }
  else {
    printf("I am the parent process, my pid is %d\n", getpid());
    printf("Waiting for child process to exit\n");
    wait(&child_status); // child_status is a pointer to an int , wait的参数是一个指向int的指针,wait会将子进程的退出状态写入这个int中
    printf("Child process exited with status %d\n", child_status);
  }
  printf("Bye\n");
}

void fork7() {
  pid_t pid[10];
  int i, childStatus;

  for (i = 0; i < 10; i++) {
    if ((pid[i] = fork()) == 0) {
      exit(100 + i);
    }
  }

  for (i = 0; i < 10; i++) {
    pid_t wpid = wait(&childStatus);
    if (WIFEXITED(childStatus)) {
      printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(childStatus));
    }
    else
      printf("Child %d terminate with abnormally\n", wpid);
  }
}

void fork8() {
  pid_t pid[10];
  int i, childStatus;

  for (i = 0; i < 10; i++) {
    if ((pid[i] = fork()) == 0) {
      exit(100 + i);
    }
  }

  for (i = 9;i >= 0; i--) {
    pid_t wpid = waitpid(pid[i], &childStatus, 0);
    if (WIFEXITED(childStatus)) {
      printf("Child %d terminated with exit status %d\n", wpid, WEXITSTATUS(childStatus));
    }
    else
      printf("Child %d terminate with abnormally\n", wpid);
  }
}

void execveExample() {
  pid_t pid;
  char* myargv[] = { "/bin/ls","-lt",NULL };
  char* myenv[] = { NULL };
  if ((pid = fork()) == 0) {
    if (execve(myargv[0], myargv, myenv) < 0) {
      printf("execve failed,%s: Command not found.\n", myargv[0]);
      perror("execve");
    }
  }

  else {
    wait(NULL);
    printf("Child process terminated\n");
    execve("/bin/ls", "/bin/ls", NULL);
  }

}