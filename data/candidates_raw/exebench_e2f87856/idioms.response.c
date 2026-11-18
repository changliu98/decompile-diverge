void swap(int *pfirstNumber, int *psecondNumber)
{
  int temp = *pfirstNumber;
  *pfirstNumber = *psecondNumber;
  *psecondNumber = temp;
}