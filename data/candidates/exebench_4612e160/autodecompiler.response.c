int utf8_decode_v2(char *str, size_t len, size_t *clen)
{
 int c;

 if (!len || !*str) {
  if (clen)
   *clen = 0;
  return -1;
 }

 if (!(*str & 0x80)) {
  if (clen)
   *clen = 1;
  return *str & 0x7f;
 }

 if ((*str & 0xe0) == 0xc0) {
  if (clen)
   *clen = 2;
  if (len < 2 || !str[1])
   return -1;
  return (*str & 0x1f) << 6 | (str[1] & 0x3f);
 }

 if ((*str & 0xf0) == 0xe0) {
  if (clen)
   *clen = 3;
  if (len < 3 || !str[1] || !str[2])
   return -1;
  return (*str & 0x0f) << 12 | (str[1] & 0x3f) << 6 | (str[2] & 0x3f);
 }

 if ((*str & 0xf8) == 0xf0) {
  if (clen)
   *clen = 4;
  if (len < 4 || !str[1] || !str[2] || !str[3])
   return -1;
  return (*str & 0x07) << 15 | (str[1] & 0x3f) << 12 | (str[2] & 0x3f) << 6 | (str[3] & 0x3f);
 }

 if (clen)
  *clen = 0;
 return -1;
}