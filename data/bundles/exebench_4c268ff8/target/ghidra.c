void swap_int(int *n,int *m)

{
  int iVar1;
  int temp;
  int *m_local;
  int *n_local;
  
  iVar1 = *n;
  *n = *m;
  *m = iVar1;
  return;
}