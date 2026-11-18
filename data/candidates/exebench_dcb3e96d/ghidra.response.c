void utf8_encode(int val,char *utf8_str)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int len;
  char *utf8_str_local;
  int val_local;
  
  len = 0;
  bVar1 = (byte)val;
  if ((val < 0) || (0x7f < val)) {
    bVar2 = (byte)(val >> 6);
    if ((val < 0x80) || (0x7ff < val)) {
      bVar3 = (byte)(val >> 0xc);
      if ((val < 0x800) || (0xffff < val)) {
        if ((0xffff < val) && (val < 0x110000)) {
          utf8_str[3] = bVar1 & 0x3f | 0x80;
          utf8_str[2] = bVar2 & 0x3f | 0x80;
          utf8_str[1] = bVar3 & 0x3f | 0x80;
          *utf8_str = (byte)(val >> 0x12) & 7 | 0xf0;
          len = 4;
        }
      }
      else {
        utf8_str[2] = bVar1 & 0x3f | 0x80;
        utf8_str[1] = bVar2 & 0x3f | 0x80;
        *utf8_str = bVar3 & 0xf | 0xe0;
        len = 3;
      }
    }
    else {
      utf8_str[1] = bVar1 & 0x3f | 0x80;
      *utf8_str = bVar2 & 0x1f | 0xc0;
      len = 2;
    }
  }
  else {
    *utf8_str = bVar1 & 0x7f;
    len = 1;
  }
  utf8_str[len] = '\0';
  return;
}