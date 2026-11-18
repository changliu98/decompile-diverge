void swap(int *k,int *i)

{
  int iVar1;
  int zero_buffer;
  int *i_local;
  int *k_local;
  
  iVar1 = *k;
  *k = *i;
  *i = iVar1;
  return;
}