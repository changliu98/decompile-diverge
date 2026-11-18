#include <assert.h>

#include <ctype.h>



void func0(const char* string, int* alphabets, int* digits, int* special) {
  *alphabets = *digits = *special = 0;
  for (int i = 0; string[i] != '\0'; i++) {
    if (isalpha(string[i]))
      (*alphabets)++;
    else if (isdigit(string[i]))
      (*digits)++;
    else
      (*special)++;
  }
}
