void __cdecl SetBit(int *A, int k)
{
    A[k >> 5] |= 1 << (k & 31);
}