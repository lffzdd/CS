#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  return EXIT_SUCCESS;
}

int sum(int *a, int n);
int array[2] = {1, 2};
int main(){
    int val = sum(array, 2);
    return val;
}
