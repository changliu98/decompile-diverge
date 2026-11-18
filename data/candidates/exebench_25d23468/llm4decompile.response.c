void shr(uint64_t x[2], unsigned int n)
{
 if (n >= 64) {
  n -= 64;
  x[0] = x[1];
  x[1] = 0;
 }
 x[0] >>= n;
 x[0] |= x[1] << (64 - n);
 x[1] >>= n;
}