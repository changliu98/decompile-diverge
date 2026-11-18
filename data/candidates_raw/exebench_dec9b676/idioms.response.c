void sbox(unsigned int *out, unsigned int *in)
{
  unsigned int i; unsigned int carry = 0;
  for (i = 0; i < 31; i++)
  {
    carry += in[i] * 121665;
    out[i] = (unsigned char)(carry & 0xff);
    carry = (carry >> 8);
  }
  carry += in[31] * 121665;
  out[31] = (unsigned char)(carry & 0xff);
  carry = (carry >> 7) * 19;
  for (i = 0; i < 31; i++)
  {
    carry += out[i];
    out[i] = (unsigned char)(carry & 0xff);
    carry = (carry >> 8);
  }
  out[i] += carry;
}