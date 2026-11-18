void sub(unsigned int out[32],const unsigned int a[32],const unsigned int b[32])
{
  unsigned int j;
  unsigned int u;
  u = 0xda;
  for (j = 0;j < 31;++j) { u += a[j] + 0xff00 - b[j]; out[j] = u & 0xff; u >>= 8; }
  u += a[j] - b[j]; out[j] = u;
}