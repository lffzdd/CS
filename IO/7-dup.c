#include "csapp.h"

int main(int argc, char const* argv[]) {
  int fd1, fd2;
  char c;

  fd1 = Open("io.txt", O_RDONLY, 0);
  fd2 = Open("io.txt", O_RDONLY, 0);
  
  Read(fd1, &c, 1);
  printf("c = %c\n", c);
  
  Read(fd2, &c, 1);
  printf("c = %c\n", c);
  
  Dup2(fd1, fd2);
  Read(fd2, &c, 1);
  printf("c = %c\n", c);

  return 0;
}
