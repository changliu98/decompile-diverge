#include  <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include <unistd.h>

#include <errno.h>

#include <stddef.h>

void removeslave(int* slave, int n) {
    int i;
    for (i=10 -1; i>=0; i--) {
        if (*(slave+i)) {
            *(slave+i)=0;
            n--;
        }
        if (n==0) return;
    }
}
