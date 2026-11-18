

#include <assert.h>

#include <string.h>



void func0(char* text) {
  for (int i = 0; text[i] != '\0'; ++i) {
    if (text[i] == ' ') {
      text[i] = '_';
    }
  }
}
