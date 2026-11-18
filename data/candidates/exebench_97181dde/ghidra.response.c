void SetBit(int *A,int k)

{
  uint flag;
  int pos;
  int i;
  int k_local;
  int *A_local;
  
  A[k / 0x20] = A[k / 0x20] | 1 << ((byte)(k % 0x20) & 0x1f);
  return;
}