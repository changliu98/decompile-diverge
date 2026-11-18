#include <stdio.h>

#include <stdlib.h>

void swapNumbers(int *pfirstNumber, int *psecondNumber){
  int temp = *pfirstNumber;
  *pfirstNumber = *psecondNumber;
  *psecondNumber = temp;
}
