void set_mac(unsigned char *to, unsigned char *from)
{
 int i;
 for(i=0; i<6; i++)
  to[i]=from[i];
}