

#include <stdio.h>

#include <string.h>

#include <assert.h>



char *func0(char *text) {
  for (int i = 0; text[i] != '\0'; i++) {
    if (text[i] == ' ' || text[i] == ',' || text[i] == '.') {
      text[i] = ':';
    }
  }
  return text;
}
