static inline int futex_get(struct futex *lock)
{
    int ret = 0;
    if (lock->count == 0)
        ret = 1;
    lock->count = 1;
    return ret;
}