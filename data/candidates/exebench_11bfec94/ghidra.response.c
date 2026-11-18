void to_hex(long x,char *c)

{
  char h [16];
  int i;
  char *c_local;
  long x_local;
  
  h._0_8_ = s_0123456789ABCDEFusage___s_<seed>_00102010._0_8_;
  h._8_8_ = s_0123456789ABCDEFusage___s_<seed>_00102010._8_8_;
  x_local = x;
  for (i = 3; -1 < i; i = i + -1) {
    c[i] = h[x_local % 0x10];
    x_local = x_local >> 4;
  }
  c[4] = '\0';
  return;
}