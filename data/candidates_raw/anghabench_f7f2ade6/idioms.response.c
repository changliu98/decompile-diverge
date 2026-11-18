static inline _Bool is_negative(long val)
{
    return (val & 0x80000000) != 0;
}