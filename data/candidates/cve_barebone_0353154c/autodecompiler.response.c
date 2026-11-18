void bit_write_UMC( EncodingEnvironmentPtr e, unsigned long symbol )
{
  unsigned char buffer[5];
  unsigned long mask;
  int i,j;

  unsigned long low = symbol;
  unsigned long range = 127;

  j=4;
  i=0;
  while (1)
  {
    if (j<0)
    {
      j=0;
      break;
    }
    buffer[j] = (unsigned char)((low & range) >> i);
    buffer[j] |= 128;
    range<<=7;
    j--;
    i+=7;
  }

  while ((j<5) && (buffer[j]&127)==0)
    j++;

  if (buffer[j] & 64)
  {
    j--;
  }

  buffer[j] &= 127;

  i=4;
  while (i>=j)
  {
    bit_write_RC(e, buffer[i]);
    i--;
  }
}