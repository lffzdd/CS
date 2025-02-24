#include"csapp.h"

// DIR* opendir(const char* name);
/* opendir 函数位于头文件 dirent.h 中, 用于打开一个目录, 返回一个指向该目录流的指针.
流指针是一个指向 dirent 结构的指针, 该结构包含目录中的文件名和 inode 号.
 */

 //  struct dirent* readdir(DIR* dirp); //每次调用 readdir 函数, 会返回流 dirp 中的下一个目录项的指针, 如果到达目录尾部或者发生错误, 则返回 NULL.且出错时设置 errno 变量.
 /*   目录项的结构如下:
   struct dirent {
     ino_t d_ino; // inode 号
     char d_name[256]; // 文件名
   }; */

   // int closedir(DIR* dirp); // 关闭目录流并释放所有资源, 成功返回 0, 失败返回 -1, 并设置 errno 变量.
   // 关闭流就是释放由 opendir 函数分配的内存, 并关闭与该目录关联的文件描述符.也就是将dirp结构体指针所指向的内存释放掉.

int main(int argc, char const* argv[]) {
  DIR* streamp;
  struct dirent* dep;

  streamp = Opendir(argv[1]);

  errno = 0;
  while ((dep = Readdir(streamp)) != NULL) {
    printf("inode: %lu, name: %s\n", dep->d_ino, dep->d_name);
  }
  if (errno != 0)
    unix_error("readdir error");

  Closedir(streamp);
  return 0;
}
