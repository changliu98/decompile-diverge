static char *to_utf8(int c, char *buf)
{
 int i = 0;
 if (c >= 0 && c <= 0x7f) {
  buf[0] = c & 0x7f;
  i = 1;
 } else if (c >= 0x80 && c <= 0x7ff) {
  buf[1] = 0x80 | (c & 0x3f);
  c = c >> 6;
  buf[0] = 0xc0 | (c & 0x1f);
  i = 2;
 } else if (c >= 0x800 && c <= 0xffff) {
  buf[2] = 0x80 | (c & 0x3f);
  c = c >> 6;
  buf[1] = 0x80 | (c & 0x3f);
  c = c >> 6;
  buf[0] = 0xe0 | (c & 0xf);
  i = 3;
 } else if (c >= 0x10000 && c <= 0x10ffff) {
  buf[3] = 0x80 | (c & 0x3f);
  c = c >> 6;
  buf[2] = 0x80 | (c & 0x3f);
  c = c >> 6;
  buf[1] = 0x80 | (c & 0x3f);
  c = c >> 6;
  buf[0] = 0xf0 | (c & 0x7);
  i = 4;
 }
 buf[i] = '\0';
 return buf;
}