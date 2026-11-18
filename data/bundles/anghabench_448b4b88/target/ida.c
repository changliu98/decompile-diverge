bool __cdecl s390_cpumsf_reached_trailer(size_t entry_sz, size_t pos)
{
  return S390_CPUMSF_PAGESZ - 4LL - ((S390_CPUMSF_PAGESZ - 1) & pos) >= entry_sz;
}