bool pmc_overflow(unsigned_long val)

{
  unsigned_long val_local;
  uint local_c;
  
  local_c = (uint)((int)val < 0);
  return local_c;
}