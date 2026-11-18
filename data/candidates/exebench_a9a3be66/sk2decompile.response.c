void byte2bits(unsigned char byte, char *bits) {
  int i;
  for (i = 7; i >= 0; i--) {
    *bits++ = (byte & (1 << i)) ? '1' : '0';
  }
  *bits = '\0';
}