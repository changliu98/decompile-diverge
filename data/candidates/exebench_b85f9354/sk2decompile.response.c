void calculate_crc(unsigned char *crc, unsigned char data) {
  unsigned char tmp;
  tmp = data ^ *crc;
  *crc = tmp;
}