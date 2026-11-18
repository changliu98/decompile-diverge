

#include <assert.h>

#include <ctype.h>

#include <string.h>



void func0(char* input, char* output) {
  int i = 0;
  while (input[i]) {
    output[i] = tolower((unsigned char)input[i]);
    i++;
  }
  output[i] = '\0';
}
