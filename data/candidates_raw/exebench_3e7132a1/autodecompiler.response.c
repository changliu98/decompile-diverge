static int
utf8_to_ucs2(unsigned short *dest, unsigned char *src)
{
 long c;
 int len;

 c = *src;
 if (c < 0x80) {
  *dest = (unsigned short) c;
  len = 1;
 } else {
  int c1, c2;

  c1 = src[1] ^ 0x80;
  if ((c1 & 0xc0) != 0)
   goto bad;
  if (c < 0xe0) {
   if (c < 0xc0)
    goto bad;
   c = (c << 6) | c1;
   if (c < 0x80)
    goto bad;
   *dest = (unsigned short) c;
   len = 2;
  } else {
   c2 = src[2] ^ 0x80;
   if ((c2 & 0xc0) != 0)
    goto bad;
   if (c < 0xf0) {
    c = ((c << 6) | c1) << 6 | c2;
    if (c < 0x800)
     goto bad;
    *dest = (unsigned short) c;
    len = 3;
   } else {
    goto bad;
   }
  }
 }

 return len;

bad:
 *dest = (unsigned short) 0x80;
 return 1;
}