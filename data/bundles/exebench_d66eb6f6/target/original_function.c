unsigned int bcd2int(unsigned char* s,int slen)
{
 unsigned int o;
 int i;
 if (slen>5)
  return 0;
 o=0;
 for(i=0;i<slen;i++)
  o=o*100+(s[i]/0x10)*10+(s[i]%0x10);
 return o;
}