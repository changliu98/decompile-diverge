char *
utf_16le_to_utf_8_truncated (const wchar_t *utf_16, char *utf_8, size_t utf_8_len)
{
  char *utf_8_start = utf_8;
  wchar_t c;
  wchar_t c2;
  unsigned int uc;

  if (utf_8_len == 0)
    return utf_8;

  while ((c = *utf_16++) != L'\0')
    {
      if (c >= L'\xd800' && c <= L'\xdfff')
 {
   c2 = *utf_16++;
   if (c2 == L'\0')
     {
       c = L'\xfffd';
     }
   else if (c2 >= L'\xdc00' && c2 <= L'\xdfff')
     {
       c = ((c - L'\xd800') << 10) + (c2 - L'\xdc00') + 0x10000;
     }
   else
     {
       c = L'\xfffd';
     }
 }
      else if (c >= L'\xe000' && c <= L'\xffff')
 {
   c = L'\xfffd';
 }

      uc = c;

      if (uc < 0x80)
 {
   if (utf_8_len < 2)
     break;
   *utf_8++ = uc;
   utf_8_len--;
 }
      else if (uc < 0x800)
 {
   if (utf_8_len < 3)
     break;
   *utf_8++ = 0xc0 | ((uc >> 6) & 0x1f);
   *utf_8++ = 0x80 | (uc & 0x3f);
   utf_8_len -= 2;
 }
      else if (uc < 0x10000)
 {
   if (utf_8_len < 4)
     break;
   *utf_8++ = 0xe0 | ((uc >> 12) & 0x0f);
   *utf_8++ = 0x80 | ((uc >> 6) & 0x3f);
   *utf_8++ = 0x80 | (uc & 0x3f);
   utf_8_len -= 3;
 }
      else
 {
   if (utf_8_len < 5)
     break;
   *utf_8++ = 0xf0 | ((uc >> 18) & 0x03);
   *utf_8++ = 0x80 | ((uc >> 12) & 0x3f);
   *utf_8++ = 0x80 | ((uc >> 6) & 0x3f);
   *utf_8++ = 0x80 | (uc & 0x3f);
   utf_8_len -= 4;
 }
    }

  *utf_8 = '\0';
  return utf_8;
}