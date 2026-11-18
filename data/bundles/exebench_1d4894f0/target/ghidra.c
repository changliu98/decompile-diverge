void stack4_replace_top(unsigned_long *s,unsigned_long e)

{
  unsigned_long e_local;
  unsigned_long *s_local;
  
  *s = *s & 0xfffffffffffffff0 | e;
  return;
}