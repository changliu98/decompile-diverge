uint bcd2int(uchar *s,int slen)

{
  int i;
  uint o;
  int slen_local;
  uchar *s_local;
  uint local_c;
  
  if (slen < 6) {
    o = 0;
    for (i = 0; i < slen; i = i + 1) {
      o = o * 100 + (s[i] / 0x10) * 10 + (uint)s[i] % 0x10;
    }
    local_c = o;
  }
  else {
    local_c = 0;
  }
  return local_c;
}