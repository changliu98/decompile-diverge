void validate_st_entry(unsigned_long *entry)

{
  unsigned_long *entry_local;
  
  *entry = *entry & 0xffffffffffffffdf;
  *entry = *entry;
  return;
}