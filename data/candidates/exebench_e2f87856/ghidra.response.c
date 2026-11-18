void swapNumbers(int *pfirstNumber,int *psecondNumber)

{
  int iVar1;
  int temp;
  int *psecondNumber_local;
  int *pfirstNumber_local;
  
  iVar1 = *pfirstNumber;
  *pfirstNumber = *psecondNumber;
  *psecondNumber = iVar1;
  return;
}