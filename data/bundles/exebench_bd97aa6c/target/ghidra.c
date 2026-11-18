void subpixels(unsigned_long p,unsigned_long *a,unsigned_long *r,unsigned_long *g,unsigned_long *b)

{
  unsigned_long *b_local;
  unsigned_long *g_local;
  unsigned_long *r_local;
  unsigned_long *a_local;
  unsigned_long p_local;
  
  *a = p >> 0x18 & 0xff;
  *r = p >> 0x10 & 0xff;
  *g = p >> 8 & 0xff;
  *b = p & 0xff;
  return;
}