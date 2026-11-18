char *func0(char *text)
{
  unsigned int i; unsigned int j;
  unsigned int crc;
  if (strlen(text) == 0)
    return strdup("None");
  crc = 0xFFFFFFFF;
  for (i = 0; text[i]; i++)
  {
    crc ^= (text[i] & 0xFF);
    for (j = 0; j < 8; j++)
    {
      if (crc & 1)
        crc = (crc >> 1) ^ 0xEDB88320;
      else
        crc = (crc >> 1);
    }
  }
  crc = ~crc;
  char *ret = (char *)malloc(9);
  if (ret)
    sprintf(ret, "%08X", crc);
  return ret;
}