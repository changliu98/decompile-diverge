static inline unsigned long long atomic_fetch_and(unsigned long long *p, unsigned long long mask)
{
 return (*p = (*p & mask));
}