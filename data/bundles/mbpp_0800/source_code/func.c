

#include <assert.h>

#include <string.h>

#include <ctype.h>



void func0(char* text, char* result) {
  int i = 0, j = 0;
  while (text[i]) {
    if (!isspace((unsigned char)text[i])) {
      result[j++] = text[i];
    }
    i++;
  }
  result[j] = '\0';
}
