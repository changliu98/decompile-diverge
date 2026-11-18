#include <stdio.h>

void reverse(char* s) {

    char* end = s;
    char temp;
    if(s){
        while(*end) {
            end++;
        }
        end--;
        while(s < end) {
            temp = *end;
            *end-- = *s;
            *s++ = temp;
        }
    }
}
