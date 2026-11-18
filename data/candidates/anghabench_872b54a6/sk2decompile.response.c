static int byte_row_johab_hangul(unsigned char c) {
  if (c >= 0x84 && c <= 0xd3)
    return c - 0x84;
  else
    return -1;
}