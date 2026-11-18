#include <string.h>

char* strcpy(char* destination, const char* s) {
    char* d = (char*)destination;
    for(;*s != '\0'; *d++ = *s++);
    *d = '\0';
    return destination;
}
