static char *utf8_to_ucs4(char *s, int *dest)
{
 int i, bits, octets;
 int c, ucs2 = 0;
 char *r;

 c = (int)*s++;
 if ((c & 0x80) == 0) {
  if (dest)
   *dest = c;
  goto done;
 }
 if ((c & 0xe0) == 0xc0) {
  octets = 2;
  c &= 0x1f;
 } else if ((c & 0xf0) == 0xe0) {
  octets = 3;
  c &= 0x0f;
 } else if ((c & 0xf8) == 0xf0) {
  octets = 4;
  c &= 0x07;
 } else if ((c & 0xfc) == 0xf8) {
  octets = 5;
  c &= 0x03;
 } else if ((c & 0xfe) == 0xfc) {
  octets = 6;
  c &= 0x01;
 } else {
  r = NULL;
  goto done;
 }
 bits = (octets - 1) * 6;
 ucs2 |= c << bits;
 for (i = 1; ; i++) {
  if (i >= octets) {
   if (dest)
    *dest = ucs2;
   goto done;
  }
  bits -= 6;
  c = (int)*s++;
  if ((c & 0xc0) != 0x80) {
   r = NULL;
   goto done;
  }
  ucs2 |= (c & 0x3f) << bits;
 }

done:
 r = s;
 return r;
}