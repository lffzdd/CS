#include "csapp.h"

void func1();
void func2();

int main() {
  // func1();
  func2();

  exit(0);
}

void func1() {
  int fd1, fd2;
  char c;

  fd1 = Open("io.txt", O_RDONLY, 0);
  fd2 = Open("io.txt", O_RDONLY, 0);
  Read(fd1, &c, 1);
  Read(fd2, &c, 1);
  printf("c = %c\n", c);
}

void func2() {
  int fd;
  char c;

  fd = Open("io.txt", O_RDONLY, 0);
  if (Fork() == 0) {
    Read(fd, &c, 1); // 子进程继承了父进程的文件描述符表,但是两个进程的文件描述符表是独立的,所以子进程读取文件描述符表中的数据不会影响父进程.
    // read系统调用会改变文件表中的文件位置,而该位置决定了read函数的读写指针.
    // 虽然两者的fd分别在两个描述符表中,但是指向的是文件表中的同一个文件表项,所以两者的读写指针是共享的.
    printf("child: c = %c\n", c);
    Close(fd); // close 只是修改了子进程的文件描述符表,并且减少了文件表中的引用计数,但是并没有真正关闭文件表项和更改文件表项中的读写指针.
    exit(0);
  }
  Wait(NULL);
  Read(fd, &c, 1);
  printf("parent: c = %c\n", c);
}