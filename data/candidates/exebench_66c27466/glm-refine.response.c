char *__cdecl sgml__utf8_get_char(const char *in, int *chr)
{
  unsigned char c0 = in[0];

  // 2-byte sequence: 110xxxxx 10xxxxxx
  if ( (c0 & 0xE0) == 0xC0 && (in[1] & 0xC0) == 0x80 )
  {
    *chr = ((c0 & 0x1F) << 6) | (in[1] & 0x3F);
    return (char *)(in + 2);
  }
  // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
  else if ( (c0 & 0xF0) == 0xE0 && (in[1] & 0xC0) == 0x80 && (in[2] & 0xC0) == 0x80 )
  {
    *chr = ((c0 & 0x0F) << 12) | ((in[1] & 0x3F) << 6) | (in[2] & 0x3F);
    return (char *)(in + 3);
  }
  // 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
  else if ( (c0 & 0xF8) == 0xF0 && (in[1] & 0xC0) == 0x80 && (in[2] & 0xC0) == 0x80 && (in[3] & 0xC0) == 0x80 )
  {
    *chr = ((c0 & 0x07) << 18) | ((in[1] & 0x3F) << 12) | ((in[2] & 0x3F) << 6) | (in[3] & 0x3F);
    return (char *)(in + 4);
  }
  // 5-byte sequence: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
  else if ( (c0 & 0xFC) == 0xF8
         && (in[1] & 0xC0) == 0x80
         && (in[2] & 0xC0) == 0x80
         && (in[3] & 0xC0) == 0x80
         && (in[4] & 0xC0) == 0x80 )
  {
    *chr = ((c0 & 0x03) << 24) | ((in[1] & 0x3F) << 18) | ((in[2] & 0x3F) << 12) | ((in[3] & 0x3F) << 6) | (in[4] & 0x3F);
    return (char *)(in + 5);
  }
  // 6-byte sequence: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
  else if ( (c0 & 0xFE) == 0xFC
         && (in[1] & 0xC0) == 0x80
         && (in[2] & 0xC0) == 0x80
         && (in[3] & 0xC0) == 0x80
         && (in[4] & 0xC0) == 0x80
         && (in[5] & 0xC0) == 0x80 )
  {
    *chr = ((c0 & 0x01) << 30) | ((in[1] & 0x3F) << 24) | ((in[2] & 0x3F) << 18) | ((in[3] & 0x3F) << 12) | ((in[4] & 0x3F) << 6) | (in[5] & 0x3F);
    return (char *)(in + 4); // Note: Preserved original return pointer logic
  }
  // 1-byte sequence: 0xxxxxxx
  else
  {
    *chr = c0;
    return (char *)(in + 1);
  }
}