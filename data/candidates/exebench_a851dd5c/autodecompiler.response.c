unsigned char fdc_crc4(unsigned char *data, size_t len)
{
 int i;
 size_t j;
 unsigned char crc = 0x0f;

 for (j = 0; ; j++, data++) {
  for (i = 7; i >= 0; i--) {
   if (j >= len)
    break;
   crc <<= 1;
   if ((data[0] >> i) & 1)
    crc |= 1;
   if (crc & 0x10)
    crc ^= 0x03;
  }
  if (j >= len)
   break;
 }

 return crc & 0x0f;
}