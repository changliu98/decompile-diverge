void swap(int *a,int *b)

{
  int iVar1;
  int box;
  int *b_local;
  int *a_local;
  
  iVar1 = *a;
  *a = *b;
  *b = iVar1;
  return;
}