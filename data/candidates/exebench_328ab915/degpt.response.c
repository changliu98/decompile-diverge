int runetochar(char *s,int c)

{
  byte bVar1;
  byte bVar2;
  int c_local;
  char *s_local;
  int local_c;
  
  if (c < 0x80) {
    *s = (byte)c;
    local_c = 1;
  }
  else if (c < 0x800) {
    *s = (byte)(c >> 6) | 0xc0;
    s[1] = (byte)c & 0x3f | 0x80;
    local_c = 2;
  }
  else {
    c_local = c;
    if (0x10ffff < c) {
      c_local = 0xfffd;
    }
    bVar1 = (byte)(c_local >> 0xc);
    bVar2 = (byte)(c_local >> 6);
    if (c_local < 0x1000) {
      *s = bVar1 | 0xe0;
      s[1] = bVar2 & 0x3f | 0x80;
      s[2] = (byte)c_local & 0x3f | 0x80;
      local_c = 3;
    }
    else {
      *s = (byte)(c_local >> 0x12) | 0xf0;
      s[1] = bVar1 & 0x3f | 0x80;
      s[2] = bVar2 & 0x3f | 0x80;
      s[3] = (byte)c_local & 0x3f | 0x80;
      local_c = 4;
    }
  }
  return local_c;
}