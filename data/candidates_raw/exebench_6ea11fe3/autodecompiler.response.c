static int lock_test(int bit, unsigned long *addr)
{
 return __sync_lock_test_and_set(addr, bit);
}