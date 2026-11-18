int unicode_to_utf8(char *buf,uint c)

{
  byte bVar1;
  char *pcVar2;
  char *q;
  uint c_local;
  char *buf_local;
  
  if (c < 0x80) {
    *buf = (byte)c;
    q = buf + 1;
  }
  else {
    if (c < 0x800) {
      *buf = (byte)(c >> 6) | 0xc0;
      pcVar2 = buf;
    }
    else {
      if (c < 0x10000) {
        *buf = (byte)(c >> 0xc) | 0xe0;
        q = buf + 1;
      }
      else {
        if (c < 0x200000) {
          *buf = (byte)(c >> 0x12) | 0xf0;
          pcVar2 = buf;
        }
        else {
          bVar1 = (byte)(c >> 0x18);
          if (c < 0x4000000) {
            q = buf + 1;
            *buf = bVar1 | 0xf8;
          }
          else {
            *buf = bVar1 >> 6 | 0xfc;
            q = buf + 2;
            buf[1] = bVar1 & 0x3f | 0x80;
          }
          *q = (byte)(c >> 0x12) & 0x3f | 0x80;
          pcVar2 = q;
        }
        q = pcVar2 + 1;
        *q = (byte)(c >> 0xc) & 0x3f | 0x80;
        q = pcVar2 + 2;
      }
      *q = (byte)(c >> 6) & 0x3f | 0x80;
      pcVar2 = q;
    }
    q = pcVar2 + 1;
    *q = (byte)c & 0x3f | 0x80;
    q = pcVar2 + 2;
  }
  *q = '\0';
  return (int)q - (int)buf;
}