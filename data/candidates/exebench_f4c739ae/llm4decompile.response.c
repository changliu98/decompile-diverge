double randum(unsigned long *seed)
{
  unsigned long i, j, k, l;
  double res;

  i = *seed & 0xfff;
  j = (*seed >> 12) & 0xfff;
  k = (*seed >> 24) & 0xff;
  l = (*seed >> 36) & 0xfff;

  i = (1555 * i + 31) % 4096;
  j = (1555 * j + 137 * i / 4096 + 31) % 4096;
  k = (1555 * k + 137 * j / 4096 + 31) % 256;
  l = (1555 * l + 137 * k / 256 + 31) % 4096;

  *seed = (l << 36) | (k << 24) | (j << 12) | i;

  res = (double) i + (double) j / 4096 + (double) k / (4096 * 4096);

  return res * 4.656612875e-10;
}