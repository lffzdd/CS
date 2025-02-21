#ifdef RUNTIME
#include <st.h>
#include <stdio.h>
#include <dlfcn.h>

void *malloc(size_t size)
{
  void *(*mallocp)(size_t size);
  char *error;

  mallocp = dlysm(RTLD_NEXT, "malloc");
  if ((error = dlerror()) != NULL)
  {
    fputs(error, stderr);
    exit(1);
  }
  char *ptr = mallocp(size);
  printf("malloc(%d) = %p\n", (int)size, ptr);
  return ptr;
}
#endif /* ifdef RUNTIME */
