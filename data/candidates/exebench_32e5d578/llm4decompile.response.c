void intToBin(uint8_t num, uint8_t *binary)
{
 uint8_t i;
 for (i = 0; i < 8; i++)
 {
  binary[i] = (num & 0x80) ? 1 : 0;
  num = num << 1;
 }
}