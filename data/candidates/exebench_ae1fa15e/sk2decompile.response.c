static int render_uint32(unsigned int value, char *buffer) {
  if (value == 0) {
    buffer[0] = '0';
    return 1;
  }
  int i = 0;
  while (value) {
    buffer[i++] = "0123456789ABCDEF"[value & 0x0F];
    value >>= 4;
  }
  return i;
}