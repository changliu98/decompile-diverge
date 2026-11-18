void swap(int *lhs,int *rhs)

{
  int iVar1;
  int temp;
  int *rhs_local;
  int *lhs_local;
  
  iVar1 = *lhs;
  *lhs = *rhs;
  *rhs = iVar1;
  return;
}