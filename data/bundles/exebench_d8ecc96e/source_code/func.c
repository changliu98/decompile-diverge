#include <string.h>

#include <stdbool.h>

char* strcpy(char* dst, const char* src) {
 size_t i = 0;
 do {
  dst[i] = src[i];
 } while (src[i++] != '\0');
 return dst;
}
