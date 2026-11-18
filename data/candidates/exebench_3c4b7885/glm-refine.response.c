void set_bit(int nr, volatile unsigned long long *addr)
{
    _bittestandset((long *)addr, nr);
}