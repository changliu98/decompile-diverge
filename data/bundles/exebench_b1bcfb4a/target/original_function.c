static inline void dpaa_set_bits(unsigned long mask,
     volatile unsigned long *p)
{
 *p |= mask;
}