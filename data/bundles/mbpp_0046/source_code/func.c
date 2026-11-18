

#include <stdio.h>

#include <stdbool.h>

#include <assert.h>



bool func0(int data[], int length) {
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j < length; j++) {
      if (data[i] == data[j]) {
        return false;
      }
    }
  }
  return true;
}
