#ifdef RUNTIME
#include<dlfcn.h>
#include<stdio.h>
#include<dlfcn.h>

void *malloc(size_t size){
  void *(*mallocp)(size_t size);
  char *error;

  mallocp = dlysm(RTLD_NEXT, "malloc");
  if((error = dlerror()) != NULL){
    fputs(error, stderr);
    exit(1);
  }
  
}
#endif /* ifdef RUNTIME */

