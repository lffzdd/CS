#include <stdio.h>
char *gets(char *dest);
int main()
{

  // printf("%s", gets(buf));
  return 0;
}
void call(){
    char buf[4];
  gets(buf);
  puts(buf);
  gets()
}
char *gets(char *dest)
{
  char *p = dest;
  for (int c = getchar(); c != EOF && c != '\n'; p++)
  {
    *p = c;
    // printf("%c", c);
    c = getchar();
  }
  // *p = '\0';
  return dest;
}