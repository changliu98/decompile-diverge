void updateCRC(unsigned int *crc, unsigned char data)
{
  int i;
  int f;
  for (i = 0; i < 8; i++)
  {
    f = (*crc & 1) ^ (data & 1);
    (*crc) = (*crc) >> 1;
    data = data >> 1;
    if (f)
    {
      *crc = *crc ^ 0x8c;
    }
  }
  *crc = *crc & 0xff;
}