void init_crcccitt_tab(void)
{
 uint16_t crc;
 uint16_t poly;
 uint16_t i;
 uint16_t j;

 poly = 0x1021;
 for (i = 0; i < 256; i++) {
  crc = 0;
  j = i << 8;
  for (j = 0; j < 8; j++) {
   if ((crc ^ j) & 0x8000)
    crc = (crc << 1) ^ poly;
   else
    crc = crc << 1;
  }
  crc_tabccitt[i] = crc;
 }
 crc_tabccitt_init = true;
}