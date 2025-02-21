#ifdef COMPILETIME

#include <stdio.h>
#include <malloc.h>

void *mymalloc(size_t size){
  void *ptr=malloc(size);
  printf("调用malloc(%d),指向%p\n",(int)size,ptr);
  return ptr;
}

void myfree(void *ptr){
  printf("调用free,指向%p\n",ptr);
  free(ptr);
}

#endif /* ifdef COMPILETIME */
