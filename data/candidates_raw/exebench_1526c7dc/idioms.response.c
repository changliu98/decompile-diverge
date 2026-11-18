static __inline__ void xchg_64(void *ptr, void *val)
{
    unsigned long v = *(uint64_t *)ptr;
    while (__sync_val_compare_and_swap((uint64_t *)ptr, v, (uint64_t)val & v) != v);
}