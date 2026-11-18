void swapNumbers(int *pFirstNum, int *pSecondNum){
  int temp = *pFirstNum;
  *pFirstNum = *pSecondNum;
  *pSecondNum = temp;
}