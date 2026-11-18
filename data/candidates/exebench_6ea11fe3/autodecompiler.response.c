static int sync_set_bit(int bit, unsigned long *addr)
{
 return __sync_lock_test_and_set(addr, bit);
}