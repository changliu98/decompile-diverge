static __inline__ unsigned long get_unaligned_be64(void *ptr)
{
    unsigned long val = *(unsigned long *)ptr;
    val = (val >> 2) + (val >> 1);
    val = (val >> 4) + val;
    val = (val >> 8) + val;
    val = (val >> 16) + val;
    val = (val >> 32) + (val >> 16);
    val = (val >> 48) + (val >> 32);
    val = (val >> 60) + (val >> 48);
    *(unsigned long *)ptr = val;
    return val & 0xffffffffffffff00UL;
}