void itoa_hex(unsigned int i, char *s) {
  unsigned int j;
  for (j = 0; j < 8; j++) {
    s[7 - j] = hex_chars[i & 0x0f];
    i >>= 4;
  }
}