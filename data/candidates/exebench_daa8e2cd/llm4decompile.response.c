void poly1305_add(unsigned char h[17], const unsigned char c[17])
{
  unsigned short u;
  unsigned i;

  u = 0;
  for (i = 0; i < 17; i++)
  {
    u += h[i] + c[i];
    h[i] = u;
    u >>= 8;
  }
}