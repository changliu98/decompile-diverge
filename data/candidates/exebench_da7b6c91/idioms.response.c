static inline void avro_refcount_set(int *refcount, int value)
{
    __sync_lock_test_and_set(refcount, value);
}