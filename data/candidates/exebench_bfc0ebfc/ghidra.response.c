void utf8_int_string(uint unicode_value,char *string)

{
  byte bVar1;
  char *string_local;
  uint unicode_value_local;
  
  if (string != (char *)0x0) {
    *string = '\0';
    bVar1 = (byte)unicode_value;
    if (unicode_value < 0x80) {
      *string = bVar1;
      string[1] = '\0';
    }
    else if (unicode_value < 0x800) {
      *string = (byte)(unicode_value >> 6) & 0x1f | 0xc0;
      string[1] = bVar1 & 0x3f | 0x80;
      string[2] = '\0';
    }
    else if (unicode_value < 0x10000) {
      *string = (byte)(unicode_value >> 0xc) & 0xf | 0xe0;
      string[1] = (byte)(unicode_value >> 6) & 0x3f | 0x80;
      string[2] = bVar1 & 0x3f | 0x80;
      string[3] = '\0';
    }
    else if (unicode_value < 0x200000) {
      *string = (byte)(unicode_value >> 0x12) & 7 | 0xf0;
      string[1] = (byte)(unicode_value >> 0xc) & 0x3f | 0x80;
      string[2] = (byte)(unicode_value >> 6) & 0x3f | 0x80;
      string[3] = bVar1 & 0x3f | 0x80;
      string[4] = '\0';
    }
  }
  return;
}