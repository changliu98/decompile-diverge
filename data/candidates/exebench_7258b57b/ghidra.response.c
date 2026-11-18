int UnicodeToUtf8(uint src,char *dest)

{
  byte bVar1;
  int len;
  char *dest_local;
  uint src_local;
  
  len = 0;
  bVar1 = (byte)src;
  if (src < 0x80) {
    dest_local = dest + 1;
    *dest = bVar1;
    len = 1;
  }
  else if (src < 0x800) {
    *dest = (byte)(src >> 6) | 0xc0;
    dest_local = dest + 2;
    dest[1] = bVar1 & 0x3f | 0x80;
    len = 2;
  }
  else {
    dest_local = dest;
    if ((src != 0xfeff) && ((src < 0xd800 || (0xdfff < src)))) {
      if (src < 0x10000) {
        *dest = (byte)(src >> 0xc) | 0xe0;
        dest[1] = (byte)(src >> 6) & 0x3f | 0x80;
        dest_local = dest + 3;
        dest[2] = bVar1 & 0x3f | 0x80;
        len = 3;
      }
      else if (src < 0x10000) {
        *dest = (byte)(src >> 0x12) | 0xf0;
        dest[1] = (byte)(src >> 0xc) & 0x3f | 0x80;
        dest[2] = (byte)(src >> 6) & 0x3f | 0x80;
        dest_local = dest + 4;
        dest[3] = bVar1 & 0x3f | 0x80;
        len = 4;
      }
    }
  }
  *dest_local = '\0';
  return len;
}