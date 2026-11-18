

#include <assert.h>

#include <stdio.h>



int func0(int deciNum) {
  int octalNum = 0;
  int countval = 1;
  int remainder;
  while (deciNum != 0) {
    remainder = deciNum % 8;
    octalNum += remainder * countval;
    countval *= 10;
    deciNum /= 8;
  }
  return octalNum;
}
