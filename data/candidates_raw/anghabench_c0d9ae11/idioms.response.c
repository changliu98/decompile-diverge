int check_crc(unsigned char *buf, int len)
{
  unsigned short crc = 0xFFFF;
  if (len < 3)
    return -1;
  while (len--)
    crc = (crc << 8) ^ crc_flex_table[(crc >> 8) ^ *buf++];
  if (crc == 0x7100)
    return 0;
  return -1;
}