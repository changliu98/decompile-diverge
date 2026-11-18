void update16(unsigned short *value, int max, int inc, int reset) {
  if (*value <= max) {
    *value += inc;
  } else {
    *value = reset;
  }
}