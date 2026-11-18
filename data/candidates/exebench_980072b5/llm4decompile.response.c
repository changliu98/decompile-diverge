void set_bit(int nr, volatile void * addr)
{
 int mask;
 volatile unsigned long *ADDR = (volatile unsigned long *) addr;

 ADDR += nr >> 6;
 mask = 1 << (nr & 0x3F);
 *ADDR |= mask;
}