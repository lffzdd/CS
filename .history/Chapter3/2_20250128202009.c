#include<stdio.h>
static void show_pointer(void *p,char*descr){
printf("Pointerfor %s at %p)n",descr,p);
printf("%sit%plt%lu\n",descr,p,(unsigned long)p);
}
int global = 0;
intuseless()(returno;)
int main （）
void*p1，*p2，*p3，*p4;
int locai = o;
void*p=malioc(100);
show_pointer((void*)&local,"local");
show_pointer((void*)&globai, "global");
show_pointer((void*)p,"heap");
show_pointer((void*)useless,"code");