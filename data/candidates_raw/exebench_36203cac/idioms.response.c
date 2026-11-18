void set_bit(int nr, unsigned long *addr)
{
    ((void) (((unsigned long *)addr)[((nr) / (8 * (unsigned long)sizeof(__u64)))] |= ((unsigned long)1 << ((nr) % (8 * (unsigned long)sizeof(__u64))))));
}