void clear_bit(int nr, volatile void * a)
{
 int * addr = (int *) a;
 int mask;

 addr += nr / 64;
 mask = 1UL << (nr % 64);
 *addr &= ~mask;
}