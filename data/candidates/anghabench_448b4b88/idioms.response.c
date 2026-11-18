static __inline__ int s390_cpumsf_reached_trailer(unsigned long entry_sz, unsigned long pos)
{
  return S390_CPUMSF_PAGESZ - 4 - (pos & (S390_CPUMSF_PAGESZ - 1)) >= entry_sz;
}