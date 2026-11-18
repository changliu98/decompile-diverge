int test_and_change_bit(int nr, volatile void * addr)
{
 int mask, retval;
 unsigned char *a = (unsigned char *) addr;

 a += nr >> 3;
 mask = 1 << (nr & 0x07);
 retval = (mask & *a) != 0;
 *a ^= mask;

 return retval?0:-1;
}