void load_and_store(unsigned_long *p,unsigned_long val)

{
  unsigned_long val_local;
  unsigned_long *p_local;
  
  *p = val + *p;
  return;
}