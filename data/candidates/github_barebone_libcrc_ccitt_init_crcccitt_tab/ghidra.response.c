/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void init_crcccitt_tab(void)

{
  uint16_t c;
  uint16_t crc;
  uint16_t j;
  uint16_t i;
  
  for (i = 0; i < 0x100; i = i + 1) {
    crc = 0;
    c = i << 8;
    for (j = 0; j < 8; j = j + 1) {
      if (((crc ^ c) & 0x8000) == 0) {
        crc = crc << 1;
      }
      else {
        crc = crc << 1 ^ 0x1021;
      }
      c = c << 1;
    }
    crc_tabccitt[i] = crc;
  }
  crc_tabccitt_init = true;
  return;
}