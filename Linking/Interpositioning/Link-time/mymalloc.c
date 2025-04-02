#ifdef LINKTIME
#include <stdio.h>

void *__real_malloc(size_t size);
void __real_free(void *ptr);

void *__wrap_malloc(size_t size){
  void *ptr=__real_malloc(size);
  printf("调用了malloc(%d),位于%p\n",(int)size,ptr);
  return ptr;
}

void __wrap_free(void *ptr){
  printf("调用了free(%p)",ptr);
  __real_free(ptr);
}
 #endif /* ifdef LINKTIME */ 
