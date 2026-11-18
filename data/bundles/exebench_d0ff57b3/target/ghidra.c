void swap_1(int *a,int *b)

{
  int iVar1;
  int c;
  int *b_local;
  int *a_local;
  
  iVar1 = *a;
  *a = *b;
  *b = iVar1;
  return;
}