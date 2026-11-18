int read_int_delta(unsigned char *buf, unsigned int *val,
                   unsigned int *last_val) {
  *val = buf[0] & 0x7f;
  if (buf[0] < 0x80) {
    *last_val += *val;
    *val = *last_val;
    return 1;
  }
  *val |= (buf[1] & 0x7f) << 7;
  if (buf[1] < 0x80) {
    *last_val += *val;
    *val = *last_val;
    return 2;
  }
  *val |= (buf[2] & 0x7f) << 14;
  if (buf[2] < 0x80) {
    *last_val += *val;
    *val = *last_val;
    return 3;
  }
  *val |= (buf[3] & 0x7f) << 21;
  if (buf[3] < 0x80) {
    *last_val += *val;
    *val = *last_val;
    return 4;
  }
  *val |= (buf[4] & 0x7f) << 28;
  *last_val += *val;
  *val = *last_val;
  return 5;
}