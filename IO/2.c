#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char const* argv[]) {
  char buf[512];
  int fd, nbytes;

  if ((fd = open("/etc/hosts", O_RDONLY)) < 0) {
    perror("open");
    exit(1);
  }
  printf("fd = %d\n", fd);

  nbytes = read(fd, buf, sizeof(buf)); // 第三个参数为buf的大小,可以跟buf的大小不一样
  if (nbytes < 0) {
    perror("read");
    exit(1);
  }
  printf("nbytes = %d\n", nbytes);
  printf("buf = %s\n", buf);


  if (fd=open("io.txt",O_APPEND|O_CREAT|O_RDWR,0644) < 0) { // RDWR 读写模式,CREAT 如果文件不存在则创建, O_APPEND 追加模式, 0644 文件权限,表示所有者有读写权限,组用户和其他用户只有读权限
    perror("open");
    exit(1);
  }
  printf("\nfd = %d\n", fd);
  if ((nbytes = write(fd, "hello world", 11)) < 0) { // write 函数位于头文件unistd.h中
    perror("write");
    exit(1);
  }

  printf("nbytes = %d\n", nbytes);
  return 0;
}
