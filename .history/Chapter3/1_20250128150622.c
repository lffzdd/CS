#include <stdio.h>

typedef struct
{
  /* data */
  int a[2];
  double d;
} struct_t;

double fun(int i)
{
  volatile struct_t s;
  s.d = 3.14;
  s.a[i] = 1073741824;
  return s.d;
}

int main(int argc, char const *argv[])
{
  /* code */
  return 0;
}

printf("%.f",fun(0));

