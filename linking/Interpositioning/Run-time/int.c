#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h>

int main(void)
{
  int *p=malloc(32);
  free(p);
  return (0);
}
