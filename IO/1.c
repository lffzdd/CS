#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const* argv[]) {
  int fd, retval;
  if ((fd = open("/etc/hosts", O_RDONLY)) < 0) {// open 位于头fcntl.h中
    perror("open");
    exit(1);
  }
  printf("fd = %d\n", fd);

  if ((retval = close(fd)) < 0) { // close 函数位于头文件unistd.h中
    perror("close");
    exit(1);
  }
  printf("retval = %d\n", retval);

  return 0;
}

