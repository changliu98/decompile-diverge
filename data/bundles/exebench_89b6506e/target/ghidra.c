void swap(int *num1,int *num2)

{
  int iVar1;
  int tmp;
  int *num2_local;
  int *num1_local;
  
  iVar1 = *num1;
  *num1 = *num2;
  *num2 = iVar1;
  return;
}