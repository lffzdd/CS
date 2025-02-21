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
    
    
    printf("You entered: %s", input);

    return 0;
}