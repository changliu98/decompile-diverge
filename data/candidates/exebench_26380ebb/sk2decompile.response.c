void CRC_Init(unsigned short *crc) {
  *crc = 0xffff;
  *crc = ~(*crc);
}