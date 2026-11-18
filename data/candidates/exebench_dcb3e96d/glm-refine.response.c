void __cdecl utf8_encode(int val, char *utf8_str)
{
  int len;

  if (val >= 0x10000 && val <= 0x10FFFF) {
    // 4-byte UTF-8 sequence
    utf8_str[3] = (val & 0x3F) | 0x80;
    utf8_str[2] = ((val >> 6) & 0x3F) | 0x80;
    utf8_str[1] = ((val >> 12) & 0x3F) | 0x80;
    *utf8_str = ((val >> 18) & 0x07) | 0xF0;
    len = 4;
  } 
  else if (val >= 0x800 && val <= 0xFFFF) {
    // 3-byte UTF-8 sequence
    utf8_str[2] = (val & 0x3F) | 0x80;
    utf8_str[1] = ((val >> 6) & 0x3F) | 0x80;
    *utf8_str = ((val >> 12) & 0x0F) | 0xE0;
    len = 3;
  } 
  else if (val >= 0x80 && val <= 0x7FF) {
    // 2-byte UTF-8 sequence
    utf8_str[1] = (val & 0x3F) | 0x80;
    *utf8_str = ((val >> 6) & 0x1F) | 0xC0;
    len = 2;
  } 
  else {
    // 1-byte UTF-8 sequence (ASCII)
    *utf8_str = val & 0x7F;
    len = 1;
  }

  // Null-terminate the string
  utf8_str[len] = 0;
}