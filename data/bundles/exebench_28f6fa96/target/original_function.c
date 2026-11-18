unsigned int
arikkei_ucs2_strncpy (const unsigned short *s, unsigned short *d, unsigned int maxlen)
{
 unsigned int di;
 const unsigned short *p;

 di = 0;
 p = s;

 if (maxlen < 0) {
  while (*p) {
   d[di] = *p;
   ++p;
   ++di;
  }
  d[di] = 0;
 } else {
  while (*p && di < maxlen) {
   d[di] = *p;
   ++p;
   ++di;
  }
  if (di < maxlen) d[di] = 0;
 }

 return di;
}