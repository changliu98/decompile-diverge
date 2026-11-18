void swap(int *a,int *b)

{
  int iVar1;
  int temp;
  int *b_local;
  int *a_local;
  
  iVar1 = *b;
  *b = *a;
  *a = iVar1;
  return;
}