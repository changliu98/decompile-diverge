void packInt32(unsigned char *buffer, int value) {
  buffer[0] = value;
  buffer[1] = value >> 8;
  buffer[2] = value >> 16;
  buffer[3] = value >> 24;
}