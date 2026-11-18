void sync_set_bit(int nr, volatile void * addr)
{
	LOCK();
	*(volatile unsigned char *) (addr + (nr >> 3)) |= 1 << (nr & 7);
	UNLOCK();
}