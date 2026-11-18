char *byte2bin(unsigned char x, char *buffer) {
  int i;
  for (i = 0; i < 8; i++) {
    buffer[i] = (x & (1 << (7 - i))) ? '1' : '0';
  }
  buffer[8] = '\0';
  return buffer;
}