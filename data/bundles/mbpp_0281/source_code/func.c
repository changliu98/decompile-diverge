

#include <stdio.h>

#include <assert.h>

#include <stdbool.h>

#include <stdlib.h>



bool func0(int *test_list, int length) {
  for (int i = 0; i < length - 1; i++) {
    for (int j = i + 1; j < length; j++) {
      if (test_list[i] == test_list[j]) {
        return false;
      }
    }
  }
  return true;
}
