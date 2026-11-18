extern __inline__ int test_and_change_bit(unsigned long nr, volatile void * addr)
{
 int mask, retval;
 volatile unsigned char *a = (volatile unsigned char *) addr;

 a += nr >> 3;
 mask = 1 << (nr & 0x07);
 retval = (mask & *a) != 0;
 *a ^= mask;
 return retval;
}