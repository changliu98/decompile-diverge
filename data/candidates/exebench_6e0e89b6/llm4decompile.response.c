void clear_bit(int nr, volatile void * a)
{
 int * addr = (int *) a;
 int mask;

 addr += nr >> 6;
 mask = 1 << (nr & 0x3F);
 *addr &= ~mask;
}