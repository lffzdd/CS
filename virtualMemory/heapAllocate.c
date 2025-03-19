#include<stdio.h>

/* 隐式列表:找到一个空闲块 */
// First fit: 遍历隐式空闲链表,找到第一个合适的空闲块
int *implicitFirstFit(int *start, int len,int *end) {
    int *p=&start;
    while (p<end &&     // p 没有超出堆的范围
       (*p&1||          // 最后一位为1,说明该块已经被分配
       *p <=len){       // 该块大小不足以分配
        p=p+(*p&-2);    // -2 为1111...1110,用于将最后一位清零,p+(*p&-2)为下一个块的地址
    }
    return p;
}

// Next fit: 从上次搜索的位置开始,找到第一个合适的空闲块

// Best fit: 找到最小的合适的空闲块
//   需要使用多个空闲列表.每个列表存储不同大小的空闲块,空闲列表越多,查找时间越长,但是内存利用率越高

// 找到一个空闲块后,malloc会使用这个空闲块,并且将剩余的空间设置为新的空闲块
void addBlock(int *p, int len) {
    int mallocLen=(len+1)>>1<<1; // 保证len为偶数
    int blockLen=*p&-2; // 获取块大小
    *p=mallocLen | 1;   // 块大小由原来的blockLen变为mallocLen,并且最后一位设置为1,表示已经被分配
    if (mallocLen<blockLen) { // 如果分配的块大小小于原块大小,则将剩余的空间设置为新的空闲块
        *(p+mallocLen)=blockLen-mallocLen;
    }
}

// 当malloc使用空闲块时,可能创建了一个新的空闲块,例如malloc(4)使用了一个大小为6的空闲块,则会创建一个大小为2的空闲块
// 当free释放掉这个malloc分配大小为4的空间,就有了两个连续的空闲块,4->2,此时若malloc(5),则无法使用这个连续的空闲块,造成了内存碎片,所以free需要合并空闲块
void freeBlock(int *p) {
    *p&=-2; // 将最后一位清零,表示未分配
    int *next=p+(*p&-2); // 获取下一个块
    if (next<end && !(*next&1)) { // 如果下一个块未分配,则合并两个块
        *p+=*next; // 将两个块合并
    }

    /* 合并下一个块很容易,但是合并上一个块则需要遍历整个堆,效率较低
    为了解决这个问题,Donald Knuth提出了一个双向链表的方法,每个块的尾部再加上一个区域footer,内容和头部完全一样,
    通过减去footer的size,就可以找到上一个空闲块的footer,从而找到上一个空闲块
     */
}