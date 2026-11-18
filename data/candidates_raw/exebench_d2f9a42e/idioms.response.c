void subbytes(unsigned int *out, unsigned int *in, unsigned int *sub)
{
  unsigned int i; unsigned int carry = 0xDA;
  for (i = 0; i < 32 - 1; i++)
  {
    carry += in[i] + 0xff00 - sub[i];
    out[i] = carry & 0xff;
    carry >>= 8;
  }
  out[32 - 1] = carry + in[32 - 1] - sub[32 - 1];
}