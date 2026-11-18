
static inline void dpaa_clear_bits(unsigned long mask,
       volatile unsigned long *p)
{
 *p &= ~mask;
}
