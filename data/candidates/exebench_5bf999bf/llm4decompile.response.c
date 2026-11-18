void clear_bit(int nr, volatile void * a)
{
 int * addr = (int *) a;
 int mask;

 addr += nr >> 3;
 mask = 1 << (nr & 0x07);
 *addr &= ~mask;
}