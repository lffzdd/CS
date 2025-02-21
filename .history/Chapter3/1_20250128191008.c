#include <stdio.h>
char *gets(char *dest);
int main()
{
  char *str;
  printf("%s", gets(str));
  return 0;
}

char *gets(char *dest)
{
  char *p = dest;
  for (int c = getchar(); c != EOF && c != '\n'; p++)
  {
    *p = c;
    printf("%c", c);
    c = getchar();
  }
  *p = '\0';
  return dest;
}