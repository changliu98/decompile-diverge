void SWAP(uint32_t *a, uint32_t *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}