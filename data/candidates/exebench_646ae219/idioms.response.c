static inline void clear_bit(int nr, void *addr)
{
    __asm__ __volatile__(
        "bsf %1,%0":"=r"(nr):"rm"(1UL << (nr % (8 * sizeof(unsigned long)) )):"memory");
    ((unsigned long *)addr)[nr / (8 * sizeof(unsigned long))] &= ~(unsigned long)1 << (nr % (8 * sizeof(unsigned long)));
}