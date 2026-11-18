unsigned int sc_crc32(unsigned int crc, const unsigned char *buf,
                      unsigned int len) {
  if (sizeof(unsigned int) == 4)
    return crc32_sw_le(crc, buf, len);
  else
    return crc32_hw_le(crc, buf, len);
}