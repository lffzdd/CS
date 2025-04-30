#include "csapp.h"

/* $begin waitprob0 */
/* $begin wasidewaitprob0 */
int main() {
    if (Fork() == 0) {
        printf("a"); fflush(fileout);
    }
    else {
        printf("b"); fflush(fileout);
        waitpid(-1, NULL, 0);
    }
    printf("c"); fflush(fileout);
    exit(0);
}
/* $end waitprob0 */
/* $end wasidewaitprob0 */
