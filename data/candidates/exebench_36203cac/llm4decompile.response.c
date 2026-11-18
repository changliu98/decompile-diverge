void set_bit(int nr, volatile void * addr)
{
 int mask;
 unsigned long *ADDR = (unsigned long *) addr;

 ADDR += nr >> 6;
 mask = 1 << (nr & 0x3f);
 *ADDR |= mask;
}