void poly1305_add(unsigned char *a, unsigned char *b)
{
 int i;
 short carry = 0;

 for (i = 0; i < 18; i++)
 {
  carry = (short) a[i] + (short) b[i] + carry;
  a[i] = (unsigned char) (carry & 0xff);
  carry >>= 8;
 }
}