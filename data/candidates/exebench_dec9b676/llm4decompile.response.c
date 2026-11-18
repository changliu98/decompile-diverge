void mult121665(unsigned char *out,const unsigned char *a)
{
  unsigned int i;
  unsigned int carry=0;
  for (i=0; i<31; i++)
    {
      carry += a[i]*121665;
      out[i]=(carry&0xff);
      carry>>=8;
    }
  carry += a[i]*121665;
  out[i]=(carry&0x7f);
  carry>>=7;
  carry*=19;
  for (i=0; i<31; i++)
    {
      carry += out[i];
      out[i]=(carry&0xff);
      carry>>=8;
    }
  carry += out[i];
  out[i]=carry;
}