void bit_write_UMC(Bit_Chain *dat, BITCODE_UMC val)
{
  int i, j;
  uchar byte[5];
  BITCODE_UMC mask;

  mask = 0x7f;
  for (i = 4; i >= 0; i--) {
    byte[i] = (val & mask) >> (7 * (4 - i));
    byte[i] |= 0x80;
    mask <<= 7;
  }
  for (i = 0; i < 4; i++) {
    if ((byte[i] & 0x7f) != 0)
      break;
  }
  if ((byte[i] & 0x40) == 0)
    i--;
  byte[i] &= 0x7f;
  for (j = 4; j >= i; j--)
    bit_write_RC(dat, byte[j]);
}