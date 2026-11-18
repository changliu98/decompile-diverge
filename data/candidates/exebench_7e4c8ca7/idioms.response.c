static void change_bit(int nr, void *addr)
{
  __asm__ __volatile__ (
    "lock btrl %0,%1"
    :"=r" ((unsigned long long) (1UL << (nr % 64)))
    :"m" (((unsigned long long *) (addr))[nr / 64])
    :"memory");
}