void __cdecl SetBit(int *A, int k)
{
  A[k / 32] |= 1 << (k % 32);
}