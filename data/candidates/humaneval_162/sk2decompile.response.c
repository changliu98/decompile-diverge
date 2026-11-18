char *_crc32(const char *str) {
  unsigned int i, j, crc;
  char *ret;
  if (strlen(str) == 0) return strdup("None");
  crc = 0xffffffff;
  for (j = 0; str[j]; j++) {
    crc ^= (unsigned char)str[j];
    for (i = 0; i < 8; i++) {
      if (crc & 1)
        crc = (crc >> 1) ^ 0xEDB88320;
      else
        crc >>= 1;
    }
  }
  crc ^= 0xffffffff;
  ret = malloc(9);
  if (ret) sprintf(ret, "%08X", crc);
  return ret;
}