void atomic_or_long(unsigned_long *v1,unsigned_long v2)

{
  unsigned_long v2_local;
  unsigned_long *v1_local;
  
  *v1 = *v1 | v2;
  return;
}