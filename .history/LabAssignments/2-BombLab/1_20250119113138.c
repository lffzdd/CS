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
    char input[3];

    // 从标准输入读取数据
    printf("Enter some text: ");
    while(fgets(input,sizeof(input),stdin)){
      printf("You entered: %s\n", input);
        // 检查是否读取到换行符，如果没有，说明还有数据未读取
        if (input[1] == '\n') {
            break;
        }
    }
    

    // printf("You entered: %s", input);

    return 0;
}