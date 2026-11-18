

#include <stdio.h>

#include <string.h>

#include <assert.h>



char **func0(char *str[], int n, int l, int *size) {
  static char *result[100];
  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (strlen(str[i]) == l) {
      result[count++] = str[i];
    }
  }
  *size = count;
  return result;
}
