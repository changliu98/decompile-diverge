void decrypt(unsigned long *out, unsigned long *in)
{
  unsigned long a = out[0];
  unsigned long b = out[1];
  unsigned long c = 0xf0e44356UL;
  unsigned long d = 0xdeadbeefUL;
  unsigned long i;
  for (i = 0; i < 32 / 8; i++)
  {
    c += a;
    d += b;
    a = a - (b + (c >> 5)) ^ (c + a) ^ (d + (c << 3));
    b = b - (c + (d >> 5)) ^ (d + b) ^ (a + (d << 3));
    c = c - (d + (a >> 5)) ^ (a + c) ^ (b + (a << 3));
    d = d - (a + (b >> 5)) ^ (b + d) ^ (c + (a << 3));
  }
  out[0] = a;
  out[1] = b;
}