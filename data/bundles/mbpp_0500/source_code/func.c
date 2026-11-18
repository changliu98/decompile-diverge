#include <stdio.h>

#include <assert.h>

#include <string.h>



char* func0(char* arr[], int size) {
  static char ans[1000] = "";
  strcpy(ans, " ");
  for (int i = 0; i < size; i++) {
    strcat(ans, " ");
    strcat(ans, arr[i]);
  }
  return ans;
}
