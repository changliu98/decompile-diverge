
static inline int a_fetch_add(volatile int *x, int v)
{
    return __sync_fetch_and_add(x, v);
}
