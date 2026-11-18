#include <assert.h>

#include <stdio.h>

#include <string.h>



void func0(int list1[], int list1_size, int list2[], int list2_size,
           int result[]) {
  for (int i = 0; i < list1_size - 1; i++) {
    result[i] = list1[i];
  }
  for (int j = 0; j < list2_size; j++) {
    result[list1_size - 1 + j] = list2[j];
  }
}
