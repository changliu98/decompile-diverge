void swap(int *firstNum, int *secondNum)
{
  int temp = *firstNum;
  *firstNum = *secondNum;
  *secondNum = temp;
}