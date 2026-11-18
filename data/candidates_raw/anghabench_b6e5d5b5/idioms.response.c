void put_le32(void *ptr, unsigned int val)
{
  unsigned char *p = (uint8_t *)ptr;
  p[0] = (val);
  p[1] = (val >> 8);
  p[2] = (val >> 16);
  p[3] = (val >> 24);
}