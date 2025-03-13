#include<stdio.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

/*
    * mmapcopy - uses mmap to copy file fd to stdout
    */

void mmapcopy(int fd, int size);

int main(int argc, char const* argv[]) {
    struct stat stat;
    int fd;

    if (argc != 2) {
        printf("usage: %s <file>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY, 0);
    fstat(fd, &stat); // fstat - get file status
    mmapcopy(fd, stat.st_size);
    return 0;
}

void mmapcopy(int fd, int size) {
    char* bufp;
    bufp = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0); // mmap - 新建一个虚拟内存区域,将文件映射到该区域
    write(1, bufp, size); // write to stdout,会出现缺页中断,将文件内容从磁盘读入内存
    return;
}