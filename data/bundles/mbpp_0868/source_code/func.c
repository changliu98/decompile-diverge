#include <assert.h>

#include <string.h>



int func0(char *a) {
  int l = 0;
  char *x = a;
  while (*x == ' ') x++;
  for (int i = 0; i < strlen(x); i++) {
    if (x[i] == ' ') {
      l = 0;
    } else {
      l++;
    }
  }
  return l;
}
