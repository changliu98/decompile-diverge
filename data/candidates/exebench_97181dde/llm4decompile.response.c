void SetBit(BitVector *A, uint32_t k)
{
    A[k/32] |= 1<<(k%32);
}