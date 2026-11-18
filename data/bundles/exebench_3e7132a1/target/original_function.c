int
_chartorune(unsigned short *rune, const char *str)
{
 int c, c1, c2;
 long l;





 c = *(unsigned char*)str;
 if(c < 0x80) {
  *rune = c;
  return 1;
 }





 c1 = *(unsigned char*)(str+1) ^ 0x80;
 if(c1 & 0xc0)
  goto bad;
 if(c < 0xe0) {
  if(c < 0xc0)
   goto bad;
  l = ((c << 6) | c1) & 0x07ff;
  if(l <= 0x007f)
   goto bad;
  *rune = l;
  return 2;
 }





 c2 = *(unsigned char*)(str+2) ^ 0x80;
 if(c2 & 0xc0)
  goto bad;
 if(c < 0xf0) {
  l = ((((c << 6) | c1) << 6) | c2) & 0xffff;
  if(l <= 0x07ff)
   goto bad;
  *rune = l;
  return 3;
 }




bad:
 *rune = 0x80;
 return 1;
}