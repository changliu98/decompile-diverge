void endian_swap32bit(void *buf)
{
  unsigned int *val = (uint32_t *)buf;
  unsigned int tmp = *val;
  tmp = (tmp & 0xff) << 24 | (tmp & (0xff << 8)) << 8 | (tmp & (0xff << 16)) >> 8 | (tmp & (0xff << 24)) >> 24;
  *val = tmp;
}