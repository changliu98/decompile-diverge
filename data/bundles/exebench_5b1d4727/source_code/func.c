#include <stdio.h>

#include <math.h>

#include <stdbool.h>

#include <stdlib.h>

float dotProduct(float* A, float* B, size_t size) {
 float sum = 0.0f;
 int i;

 for (i = 0; i < size; i++) {
  sum += A[i] * B[i];
 }

 return sum;
}
