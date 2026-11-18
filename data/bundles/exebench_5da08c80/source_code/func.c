#include <stdio.h>

#include <math.h>

#include <stdbool.h>

#include <stdlib.h>

bool mmeq(float* A, float* B, size_t rows, size_t cols) {
 int i;

 for (i = 0; i < rows * cols; i++) {
  if (A[i] != B[i]) {
   return false;
  }
 }
 return true;
}
