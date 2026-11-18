
static inline void atomic_clear_mask(unsigned long mask, unsigned long *addr)
{
 *addr &= ~mask;
}
