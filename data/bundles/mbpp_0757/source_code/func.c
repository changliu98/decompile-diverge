#include <stdio.h>

#include <string.h>

#include <assert.h>



char* func0(char* test_list[], int size) {
  int count = 0;
  for (int idx = 0; idx < size; idx++) {
    for (int idxn = idx; idxn < size; idxn++) {
      char reversed[100];
      int len = strlen(test_list[idx]);
      for (int i = 0; i < len; i++) {
        reversed[i] = test_list[idx][len - 1 - i];
      }
      reversed[len] = '\0';
      if (strcmp(test_list[idxn], reversed) == 0) {
        count++;
      }
    }
  }
  static char result[12];
  sprintf(result, "%d", count);
  return result;
}
