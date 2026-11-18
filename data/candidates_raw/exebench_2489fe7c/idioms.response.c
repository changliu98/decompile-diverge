void crc_update(unsigned int *crc, unsigned char data)
{
  int i;
  for (i = 0; i < 8; i++) {
    *crc = (*crc << 1);
    if (data & 1)
      *crc ^= 0x8005;
    data = data >> 1;
  }
  *crc = (*crc & 0xffff);
}