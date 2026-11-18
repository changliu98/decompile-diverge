void crc8_byte(unsigned int *crc, unsigned char b)
{
 int i;
 for (i = 0; i < 9; i++) {
  int carry = (*crc ^ b) & 1;
  *crc >>= 1;
  b >>= 1;
  if (carry)
   *crc ^= 0x8c;
 }
 *crc &= 0xff;
}