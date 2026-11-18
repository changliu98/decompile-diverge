

#include <stdio.h>

#include <string.h>

#include <assert.h>



char *func0(char *test_tup[], int size) {
  static char res[1000];
  strcpy(res, "");
  char delim[] = "-";
  for (int i = 0; i < size; i++) {
    strcat(res, test_tup[i]);
    if (i < size - 1) {
      strcat(res, delim);
    }
  }
  return res;
}
