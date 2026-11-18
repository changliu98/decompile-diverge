static int UnpackImmediate(unsigned int value, unsigned int *immediate,
                           unsigned int *shift) {
  int i;
  if (value == 0) {
    *immediate = 0;
    *shift = 0;
    return 1;
  }
  for (i = 0; i < 15; i++) {
    if ((value & 3) != 0 && value < 256) {
      *immediate = value;
      *shift = i;
      return 1;
    }
    if ((value & 3) != 0) return 0;
    value >>= 2;
  }
  return 0;
}