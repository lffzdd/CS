#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const* argv[]) {
  printf("h");
  printf("e");
  printf("l");
  printf("l");
  printf("o");
  printf("\n");

  fflush(stdout); //fflush函数用于刷新流,将流中的数据立即输出到文件中.

  // strace 追踪发现,printf函数在输出字符时,并没有立即输出到文件中,而是先输出到缓冲区中,等到缓冲区满了或者遇到换行符时,才将缓冲区中的数据输出到文件中. 这个缓冲区是为了减少系统调用的次数,提高效率,它是一个结构体中的数组
  return 0;
}
