void stack4_push(unsigned_long *s,unsigned_long e)

{
  unsigned_long e_local;
  unsigned_long *s_local;
  
  *s = *s << 4 | e;
  return;
}