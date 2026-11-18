void swapNumbers(int *pFirstNum,int *pSecondNum)

{
  int iVar1;
  int temp;
  int *pSecondNum_local;
  int *pFirstNum_local;
  
  iVar1 = *pFirstNum;
  *pFirstNum = *pSecondNum;
  *pSecondNum = iVar1;
  return;
}