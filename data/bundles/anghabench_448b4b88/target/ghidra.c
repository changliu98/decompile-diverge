bool s390_cpumsf_reached_trailer(size_t entry_sz,size_t pos)

{
  size_t payload;
  size_t pos_local;
  size_t entry_sz_local;
  uint local_c;
  
  local_c = (uint)(entry_sz <=
                  ((long)S390_CPUMSF_PAGESZ + -4) - (pos & (long)(S390_CPUMSF_PAGESZ + -1)));
  return local_c;
}