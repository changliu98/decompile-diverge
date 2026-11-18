int sync_test_and_set_bit(int nr, volatile void * addr)
{
	int mask, retval;
	volatile unsigned char *a = (volatile unsigned char *) addr;

	LOCK();
	mask = 1 << (nr & 0x07);
	retval = (mask & *a) != 0;
	*a |= mask;
	UNLOCK();
	return -retval;
}