#include <sys/syscall.h>

void int2str(int value, int i, char* output){
    int j;
    while(i){
        j = (value / i) % 10;
        *output++ = '0' + j;
        i /= 10;
    }
}
