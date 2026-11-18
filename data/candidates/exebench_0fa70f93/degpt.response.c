void atomic_clear_mask(unsigned_long mask,unsigned_long *addr)

{
  unsigned_long *addr_local;
  unsigned_long mask_local;
  
  *addr = (mask ^ 0xffffffffffffffff) & *addr;
  return;
}