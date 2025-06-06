#include <stdio.h>
#include <stdlib.h>

static void show_pointer(void *p, char *descr)
{
  // printf("Pointer for %s at %p)n", descr, p);
  printf("%s\t%p\t%lu\n", descr, p, (unsigned long)p);
}

int global = 0;

int useless() { return 0; }

int main()
{
  void *p1, *p2, *p3, *p4;
  int local = 0;
  void *p = malloc(100);

  show_pointer((void *)&local, "stack\t\t");
  show_pointer((void *)&global, "global\tvar\t");
  show_pointer((void *)p, "heap\t\t");
  show_pointer((void *)useless, "global\tfunc\t");

  return 0;
}