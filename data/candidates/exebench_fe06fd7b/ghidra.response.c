void descending2(int *a,int *b)

{
  int iVar1;
  int temp;
  int *b_local;
  int *a_local;
  
  iVar1 = *a;
  if (*a < *b) {
    *a = *b;
    *b = iVar1;
  }
  return;
}