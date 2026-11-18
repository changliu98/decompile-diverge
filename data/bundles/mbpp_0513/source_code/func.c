

#include <assert.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

char** func0(int* test_tup, int size, char* K) {
  char** res = malloc(2 * size * sizeof(char*));
  int j = 0;
  for (int i = 0; i < size; i++) {
    asprintf(&res[j++], "%d", test_tup[i]);
    res[j++] = K;
  }
  return res;
}
