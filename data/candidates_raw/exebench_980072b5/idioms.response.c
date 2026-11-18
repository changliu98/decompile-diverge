static inline void set_bit(int nr, void *addr)
{
    ((unsigned long *)addr)[(nr / 64)] |= (1UL << (nr % 64));
}