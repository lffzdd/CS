#include <stdio.h>
char *gets(char *dest);
int main()
{
}

char *gets(char *dest)
{
  char *p = dest;
  for (int c = getchar(); c != EOF&&c!=; p++)
  {
    *p = c;
    printf("%c", c);
    c = getchar();
  }
}