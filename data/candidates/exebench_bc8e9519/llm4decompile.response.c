void generic_set_bit(int nr, volatile void * addr)
{
 int mask;







 *(volatile unsigned long *) (addr + (nr >> 5)) |= (1L << (nr & 0x1f));
}