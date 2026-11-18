#include <unistd.h>

#include <string.h>

#include <time.h>

int str_linecount(char *str, int linelen, int *x) {
  int lines = 1;
  while(*str != '\0') {
    if (*str == '\n') {
      ++lines;
      *x = 0;
    } else {
      ++(*x);
      if (*x >= linelen) {
        ++lines;
        *x = 0;
      }
    }
    ++str;
  }
  return lines;
}
