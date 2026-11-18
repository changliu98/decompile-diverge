void ltox(uint value,char *str)

{
  char tab [16];
  int i;
  char *str_local;
  uint value_local;
  
  tab._0_8_ = s_0123456789ABCDEFusage___s_<seed>_00102010._0_8_;
  tab._8_8_ = s_0123456789ABCDEFusage___s_<seed>_00102010._8_8_;
  value_local = value;
  for (i = 0; i < 8; i = i + 1) {
    str[9 - i] = tab[value_local & 0xf];
    value_local = value_local >> 4;
  }
  *str = '0';
  str[1] = 'x';
  str[10] = '\n';
  str[0xb] = '\0';
  return;
}