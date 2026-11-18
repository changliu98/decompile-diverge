uint32_t __cdecl sc_crc32(uint32_t crc, const void *buf, size_t len)
{
  return crc32_sw_le(crc, buf, len);
}