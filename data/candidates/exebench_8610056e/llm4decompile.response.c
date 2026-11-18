extern __inline__ int test_and_set_bit(int nr, volatile void * addr)
{
 int mask, retval;
 LOCK();
 mask = 1 << (nr & 0x07);
 retval = (mask & *(volatile unsigned char *) addr) != 0;
 *(volatile unsigned char *) addr |= mask;
 UNLOCK();
 return -retval;
}