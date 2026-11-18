void dpaa_clear_bits(unsigned_long mask,unsigned_long *p)

{
  unsigned_long *p_local;
  unsigned_long mask_local;
  
  *p = *p & (mask ^ 0xffffffffffffffff);
  return;
}