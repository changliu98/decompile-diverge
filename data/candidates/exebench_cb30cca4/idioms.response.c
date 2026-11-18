void swapNumbers(int *firstNum, int *secondNum)
{
  int temp = *firstNum;
  *firstNum = *secondNum;
  *secondNum = temp;
}