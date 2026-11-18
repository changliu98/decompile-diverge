void swap(int *p,int *q)

{
  int iVar1;
  int temp;
  int *q_local;
  int *p_local;
  
  iVar1 = *q;
  *q = *p;
  *p = iVar1;
  return;
}