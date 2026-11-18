int check_crc_flex(unsigned char *buf, int len) {
  unsigned short crc = 0xffff;
  if (len < 3) return -1;
  while (len--) crc = (crc << 8) ^ crc_table[((crc >> 8) ^ *buf++) & 0xff];
  if (crc == 0x7030) return 0;
  return -1;
}