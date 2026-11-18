char *utf8_to_ucs4(const char *source, wchar_t *result)
{
 wchar_t ch;
 wchar_t octet_count;
 wchar_t bits_count;
 wchar_t i;

 ch = *source;

 if (ch < 0x80) {
  if (result)
   *result = ch;
  return (char *)source + 1;
 }

 if ((ch & 0xE0) == 0xC0) {
  octet_count = 2;
  ch &= 0x1F;
 } else if ((ch & 0xF0) == 0xE0) {
  octet_count = 3;
  ch &= 0x0F;
 } else if ((ch & 0xF8) == 0xF0) {
  octet_count = 4;
  ch &= 0x07;
 } else if ((ch & 0xFC) == 0xF8) {
  octet_count = 5;
  ch &= 0x03;
 } else if ((ch & 0xFE) == 0xFC) {
  octet_count = 6;
  ch &= 0x01;
 } else {
  return NULL;
 }

 bits_count = (octet_count - 1) * 6;
 ch <<= bits_count;

 for (i = 1; i < octet_count; i++) {
  source++;
  bits_count -= 6;

  if ((*source & 0xC0) != 0x80)
   return NULL;

  ch |= (*source & 0x3F) << bits_count;
 }

 if (result)
  *result = ch;

 return (char *)source + 1;
}