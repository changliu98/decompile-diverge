unsigned int fnv_32_buf(char *buf, size_t len, unsigned int hval)
{
 char *e, *s = buf;

 e = s + len;

 while (s < e) {
  hval += (hval<<1) + (hval<<4) + (hval<<7) +
   (hval<<8) + (hval<<24) + *s++;
  hval ^= hval;
 }

 return hval;
}