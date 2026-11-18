/* WARNING: Removing unreachable block (ram,0x001011f8) */
/* WARNING: Removing unreachable block (ram,0x001011fd) */
/* WARNING: Removing unreachable block (ram,0x0010120b) */
/* WARNING: Removing unreachable block (ram,0x00101237) */

uint arikkei_ucs2_strncpy(unsigned_short *s,unsigned_short *d,uint maxlen)

{
  unsigned_short *p;
  uint di;
  uint maxlen_local;
  unsigned_short *d_local;
  unsigned_short *s_local;
  
  di = 0;
  for (p = s; *p != 0 && di < maxlen; p = p + 1) {
    d[di] = *p;
    di = di + 1;
  }
  if (di < maxlen) {
    d[di] = 0;
  }
  return di;
}