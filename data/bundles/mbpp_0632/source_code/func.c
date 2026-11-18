

#include <stdio.h>

#include <assert.h>



void func0(int num_list[], int size, int result[]) {
  int zero_count = 0;
  int j = 0;
  for (int i = 0; i < size; i++) {
    if (num_list[i] == 0) {
      zero_count++;
    } else {
      result[j++] = num_list[i];
    }
  }
  for (int i = 0; i < zero_count; i++) {
    result[j++] = 0;
  }
}
