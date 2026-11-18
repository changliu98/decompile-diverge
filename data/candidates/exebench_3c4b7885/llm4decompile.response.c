void set_bit(int nr, volatile void * addr)
{
 int mask;

 addr += nr >> 3;
 mask = 1 << (nr & 0x07);
 *(volatile unsigned char *)addr |= mask;
}