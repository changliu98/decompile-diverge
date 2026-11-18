#include <stdio.h>

#include <dirent.h>

#include <stdbool.h>

#include <string.h>

void int2str(int value, int i, char* output){
    int j;
    char *p = output;
    while(i){
        j = (value / i) % 10;
        *output++ = '0' + j;
        i /= 10;
    }
    *output = '\0';
}
