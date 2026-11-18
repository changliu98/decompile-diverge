unsigned int crc32(unsigned int crc, void *buf, unsigned long len)
{
  return (crc32_sw_le(crc, buf, len));
}