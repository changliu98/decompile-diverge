Fnv32_t __cdecl fnv_32_buf(void *buf, size_t len, Fnv32_t hval)
{
    unsigned __int8 *bp = (unsigned __int8 *)buf;
    unsigned __int8 *end = bp + len;

    while (bp < end)
    {
        hval = (hval * 16777619) ^ *bp;
        bp++;
    }
    
    return hval;
}