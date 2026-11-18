void encode_int(char *c,int i)

{
  bool bVar1;
  int negative;
  int i_local;
  char *c_local;
  
  bVar1 = false;
  if (i < 1) {
    i_local = -i;
    bVar1 = true;
    c_local = c;
  }
  else {
    c_local = c;
    if ((i & 0x7c00U) != 0) {
      c_local = c + 1;
      *c = (byte)(i >> 10) & 0x1f | 0x40;
    }
    i_local = i;
    if ((i & 0x3f0U) != 0) {
      *c_local = (byte)(i >> 4) & 0x3f | 0x40;
      c_local = c_local + 1;
    }
  }
  if ((i_local & 0xfU) == 0) {
    *c_local = ' ';
  }
  else {
    *c_local = (byte)i_local & 0xf | 0x20;
  }
  if (!bVar1) {
    *c_local = *c_local | 0x10;
  }
  c_local[1] = '\0';
  return;
}