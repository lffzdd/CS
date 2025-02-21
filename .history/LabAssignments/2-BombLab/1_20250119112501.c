/* #include <stdio.h>

int main(int argc, char **argv)
{
  printf("Number of arguments: %d\n", argc);
  for (int i = 0; i < argc; i++)
  {
    printf("argv[%d]: %s\n", i, argv[i]);
  }
  return 0;
} */
#include <stdio.h>

int main() {
    char input[2];

    // 从标准输入读取数据
    printf("Enter some text: ");
    fgets(input, sizeof(input), stdin);
    /* 
    1.输入流向 fgets 中输入数据：是的，fgets 从输入流中读取数据并存储到 input 缓冲区中。
    2.缓冲区大小：缓冲区 input 的大小不一定要能装满整个输入流的数据。fgets 只会读取最多 n-1 个字符。如果输入的数据超过缓冲区大小，fgets 会在下一次调用时继续读取剩余的数据。
     */
    // 向标准输出打印数据
    printf("You entered: %s", input);

    return 0;
}