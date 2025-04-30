/* $begin forkprob2 */
#include "csapp.h"

void end(void) {
    printf("2"); fflush(fileout);
}

int main() {
    if (Fork() == 0)
        atexit(end);
    if (Fork() == 0) {
        printf("0"); fflush(fileout);
    }
    else {
        printf("1"); fflush(fileout);
    }
    exit(0);
}
/* $end forkprob2 */

