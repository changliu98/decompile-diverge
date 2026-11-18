void decrease_order(int *num1,int *diff)

{
  int iVar1;
  int tmp;
  int *diff_local;
  int *num1_local;
  
  if (*num1 < *diff) {
    iVar1 = *num1;
    *num1 = *diff;
    *diff = iVar1;
  }
  return;
}