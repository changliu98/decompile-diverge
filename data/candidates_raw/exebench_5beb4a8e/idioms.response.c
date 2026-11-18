void hash(unsigned char *out, unsigned long *in)
{
  unsigned long carry = 0;
  unsigned int i;
  for (i = 0; i < 16; i++) {
    carry += in[i];
    out[i] = (unsigned char) carry;
    carry >>= 8;
  }
  carry += in[16];
  out[16] = (unsigned char) (carry & 3);
  carry >>= 2;
  carry = (carry * 5);
  for (i = 0; i < 16; i++) {
    carry += out[i];
    out[i] = (unsigned char) carry;
    carry >>= 8;
  }
  out[16] += (unsigned char) carry;
}