#include <stdlib.h>

#include <stdio.h>

#include <math.h>

#include <string.h>

void InvMat22(float invA[],float A[]) {


  float detA = A[0]*A[3]-A[1]*A[2];

  invA[0] = 1/detA * A[3];
  invA[1] = -1/detA * A[1];
  invA[2] = -1/detA * A[2];
  invA[3] = 1/detA * A[0];

}
