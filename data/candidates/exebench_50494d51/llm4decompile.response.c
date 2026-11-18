void set_bit(int nr, volatile void * addr)
{
 *((volatile unsigned long *) addr) |= 1L << (nr % 64);
}