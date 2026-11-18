void reverseIntRange(int *pStart,int *pEnd,int size)

{
  int iVar1;
  int temp;
  int size_local;
  int *pEnd_local;
  int *pStart_local;
  
  iVar1 = *pStart;
  *pStart = size - *pEnd;
  *pEnd = size - iVar1;
  return;
}