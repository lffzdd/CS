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
  printf("%f\n", fun(0));
  printf("%f\n", fun(1));
  printf("%f\n", fun(2));
  return 0;
}
