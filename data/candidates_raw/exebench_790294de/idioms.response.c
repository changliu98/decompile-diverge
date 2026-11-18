static __inline__ void xchg_set(void *addr, unsigned long mask)
{
    unsigned long *a = addr;
    unsigned long old = *a; unsigned long new = *a | mask;
    while (__sync_val_compare_and_swap(a, old, new) != old);
}