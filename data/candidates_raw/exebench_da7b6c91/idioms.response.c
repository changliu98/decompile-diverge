static inline void atomic_int_set(int *refcount, int value)
{
    __sync_lock_test_and_set(refcount, value);
}