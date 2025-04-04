#include"../code/include/csapp.h"

int main(int argc, char const* argv[]) {
  struct stat stat;
  char* type, * readok;


  Stat(argv[1], &stat);

  if (S_ISREG(stat.st_mode))
    type = "regular";
  else if (Sq_ISDIR(stat.st_mode))
    type = "directory";
  else
    type = "other";
  if ((stat.st_mode & S_IRUSR))
    readok = "yes";
  else
    readok = "no";

  printf("type: %s, read: %s\n", type, readok);
  return 0;
}
