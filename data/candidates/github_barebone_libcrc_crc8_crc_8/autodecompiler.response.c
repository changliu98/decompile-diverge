unsigned char crc_8(unsigned char *data, unsigned long length)
{
 unsigned char crc = 0;
 unsigned long i;
 unsigned char *p = data;

 if (p) {
  for (i = 0; i < length; i++) {
   crc = sht75_crc_table[crc ^ *p++];
  }
 } else {
  return crc;
 }

 return crc;
}