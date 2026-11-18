void validate_rt_entry(unsigned_long *entry)

{
  unsigned_long *entry_local;
  
  *entry = *entry & 0xffffffffffffffdf;
  *entry = *entry & 0xffffffffffffff3f;
  *entry = *entry;
  *entry = *entry | 3;
  return;
}