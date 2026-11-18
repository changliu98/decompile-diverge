void entry_clr_protected(unsigned_long *entry)

{
  unsigned_long *entry_local;
  
  *entry = *entry & 0xfffffffffffffdff;
  *entry = *entry;
  return;
}