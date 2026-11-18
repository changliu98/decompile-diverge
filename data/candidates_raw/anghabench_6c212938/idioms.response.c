void htonll(void *dest, unsigned int n)
{
  unsigned char *d = (uint8_t *)dest;
  d[0] = n;
  d[1] = n >> 8;
  d[2] = n >> 16;
  d[3] = n >> 24;
  d[4] = n >> 32;
  d[5] = n >> 40;
  d[6] = n >> 48;
  d[7] = n >> 56;
}