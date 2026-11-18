int sync_test_and_change_bit(int thread, struct futex *lock)
{
    __asm__ __volatile__ (
        "lock btc %1,%0"
        :"=m"(*lock)
        :"ir"(thread));
    return -__builtin_expect(!!(__builtin_constant_p(lock) && (lock) != 0), 0);
}