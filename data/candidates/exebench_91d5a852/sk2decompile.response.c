void to_bytes(int i, unsigned char *bytes) {
  bytes[0] = i;
  bytes[1] = i >> 8;
  bytes[2] = i >> 16;
  bytes[3] = i >> 24;
}