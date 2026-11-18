#include  <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include <unistd.h>

#include <errno.h>

#include <stddef.h>

void shiftarray(int* a) {
    int i;
    for (i=0; i<10 -1; i++) *(a+i)=*(a+i+1);
    *(a+10 -1)=-1;
}
