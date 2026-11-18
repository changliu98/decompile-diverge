int test_and_set_bit(int bit, void *addr)
{
    unsigned long *l = addr;
    return -__sync_lock_test_and_set(&l[bit], 1);
}