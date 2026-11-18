#include <stdio.h>

#include <stdlib.h>

void swapNumbers(int *pFirstNum, int *pSecondNum){
  int temp = *pFirstNum;
  *pFirstNum = *pSecondNum;
  *pSecondNum = temp;
}
