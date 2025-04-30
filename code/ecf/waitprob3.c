#include "csapp.h"

/* $begin waitprob3 */
int main() {
    if (fork() == 0) {
        printf("a"); fflush(fileout);
        exit(0);
    }
    else {
        printf("b"); fflush(fileout);
        waitpid(-1, NULL, 0);
    }
    printf("c"); fflush(fileout);
    exit(0);
}
/* $end waitprob3 */
