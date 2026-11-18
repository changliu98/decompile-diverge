static int utf8_encode(char *buf, int c)
{
 int len;

 if (c < 0x80) {
  buf[0] = c;
  len = 1;
 } else if (c < 0x800) {
  buf[0] = 0xc0 | (c >> 6);
  buf[1] = 0x80 | (c & 0x3f);
  len = 2;
 } else {
  if (c > 0x10ffff)
   c = 0xfffd;
  if (c < 0x1000) {
   buf[0] = 0xe0 | (c >> 12);
   buf[1] = 0x80 | ((c >> 6) & 0x3f);
   buf[2] = 0x80 | (c & 0x3f);
   len = 3;
  } else {
   buf[0] = 0xf0 | (c >> 18);
   buf[1] = 0x80 | ((c >> 12) & 0x3f);
   buf[2] = 0x80 | ((c >> 6) & 0x3f);
   buf[3] = 0x80 | (c & 0x3f);
   len = 4;
  }
 }

 return len;
}