void __cdecl swapfloat(float *flt)
{
    uint32_t *p = (uint32_t *)flt;
    *p = (_byteswap_ulong(*p)); // or __builtin_bswap32(*p) on GCC/Clang
}