int utf8_encode(char *buf, unsigned int c)
{
 char *p = buf;

 if (c < 0x80) {
  *p++ = c;
 } else if (c < 0x800) {
  *p++ = 0xc0 | (c >> 6);
 } else if (c < 0x10000) {
  *p++ = 0xe0 | (c >> 12);
 } else if (c < 0x200000) {
  *p++ = 0xf0 | (c >> 18);
 } else if (c < 0x4000000) {
  *p++ = 0xf8 | (c >> 24);
 } else {
  *p++ = 0xfc | (c >> 30);
  *p++ = 0x80 | ((c >> 24) & 0x3f);
 }
 if (c < 0x4000000)
  *p++ = 0x80 | ((c >> 18) & 0x3f);
 if (c < 0x10000)
  *p++ = 0x80 | ((c >> 12) & 0x3f);
 *p++ = 0x80 | ((c >> 6) & 0x3f);
 *p++ = 0x80 | (c & 0x3f);
 *p = '\0';
 return p - buf;
}