void __cdecl neg_s(const float *source, float *target)
{
    unsigned int bits = *(unsigned int *)source;
    bits ^= 0x80000000;
    *(unsigned int *)target = bits;
}