static int read_int(unsigned char *buf, unsigned int *val) {
  *val = buf[0] & 0x7f;
  if (buf[0] < 0x80) return 1;
  *val |= (buf[1] & 0x7f) << 7;
  if (buf[1] < 0x80) return 2;
  *val |= (buf[2] & 0x7f) << 14;
  if (buf[2] < 0x80) return 3;
  *val |= (buf[3] & 0x7f) << 21;
  if (buf[3] < 0x80) return 4;
  *val |= (buf[4] & 0x7f) << 28;
  return 5;
}