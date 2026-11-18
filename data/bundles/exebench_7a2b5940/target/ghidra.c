char * tcp_strflags(char *s,uint flags)

{
  int bit;
  char *p;
  char *ftab;
  uint flags_local;
  char *s_local;
  
  p = s;
  for (bit = 0; bit < 8; bit = bit + 1) {
    if ((flags & 1 << ((byte)bit & 0x1f)) != 0) {
      *p = "FSRPAYXY"[bit];
      p = p + 1;
    }
  }
  *p = '\0';
  return s;
}