static inline unsigned long long xfs_mask_uint64(unsigned long long *p, unsigned long long mask)
{
 return (*p = (*p & mask));
}