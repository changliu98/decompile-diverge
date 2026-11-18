#include <stdio.h>

#include <sys/time.h>

static void argorder(int ix1, int ix2, int *ox1, int *ox2)
{
    if (ix1 > ix2) {
        int tmp;
        tmp = ix1;
        ix1= ix2;
        ix2 = tmp;
    }
    *ox1 = ix1;
    *ox2 = ix2;
}
