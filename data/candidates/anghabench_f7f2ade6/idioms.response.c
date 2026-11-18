static inline _Bool pmc_overflow(long val)
{
    return (val & 0x80000000) != 0;
}