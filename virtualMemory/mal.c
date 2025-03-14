#include<stdio.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#ifndef __USE_MISC
#define __USE_XOPEN_EXTENDED
#define __USE_MISC
#endif

#include<unistd.h>

void alloc_on_brk();
void alloc();
void brk_test();
void print_brk();

int main(int argc, char const* argv[]) {
	alloc_on_brk();
	return 0;
}


void print_brk() {
	printf("brk: %p\n", sbrk(0));
}


// malloc 在堆不够用时会调用 sbrk 来扩展堆,free 后不会调用 sbrk 来缩小堆
void brk_test() {
	void* heap_start = sbrk(0);
	printf("Heap start: %p\n", heap_start);

	void* ptr = malloc(1024);
	printf("malloc ptr: %p\n", ptr);
	printf("brk: %p\n", sbrk(0));

	free(ptr);
	printf("brk: %p\n", sbrk(0));

	ptr = malloc(1025);
	printf("malloc ptr: %p\n", ptr);
	printf("brk: %p\n", sbrk(0));
	free(ptr);
	printf("brk: %p\n", sbrk(0));
}


// malloc 分配内存,小分配使用 brk,大分配使用 mmap
void alloc() {
	void* heap_start = sbrk(0);
	printf("Heap start: %p\n", heap_start);

	void* small_alloc = malloc(1024);  // 小分配
	printf("Small malloc (1KB): %p\n", small_alloc);

	void* large_alloc = malloc(200000);  // 大分配（通常用 mmap）
	printf("Large malloc (200KB): %p\n", large_alloc);

	void* heap_end = sbrk(0);
	printf("Heap end: %p\n", heap_end);

	free(small_alloc);
	free(large_alloc);
}


void alloc_on_brk() {
	print_brk();
	void* p1 = malloc(4 * sizeof(int));
	print_brk();
	void* p2 = malloc(4 * sizeof(int));
	print_brk();
	void* p3 = malloc(5 * sizeof(int));
	print_brk();
	free(p1);
	free(p2);
	free(p3);
	print_brk();
}