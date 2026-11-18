static inline void set_bit(int nr, unsigned long *addr)
{
    ((addr))[(nr)/(sizeof(unsigned long) * 8)] |= (1UL << ((nr) % (sizeof(unsigned long) * 8)));
}