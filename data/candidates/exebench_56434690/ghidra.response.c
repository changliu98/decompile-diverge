void swap(int *m,int *n)

{
  int iVar1;
  int x;
  int *n_local;
  int *m_local;
  
  iVar1 = *m;
  *m = *n;
  *n = iVar1;
  return;
}