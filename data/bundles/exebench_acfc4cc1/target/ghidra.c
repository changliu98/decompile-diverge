void reorder(int *a,int *b)

{
  int iVar1;
  int t;
  int *b_local;
  int *a_local;
  
  if (*b < *a) {
    iVar1 = *a;
    *a = *b;
    *b = iVar1;
  }
  return;
}