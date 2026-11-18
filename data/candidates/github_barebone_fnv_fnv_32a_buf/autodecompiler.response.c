unsigned int fnv_32a_buf(char *buf, size_t len, unsigned int hval)
{
 unsigned char *bp = (unsigned char *) buf;
 unsigned char *be = bp + len;




 while(bp < be) {





  hval ^= (unsigned int)*bp++;




  hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24);

 }

 return hval;
}