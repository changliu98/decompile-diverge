void BinaryFiles__swap_bytes32(unsigned int *val) {
  unsigned int orig = *val;
  unsigned int swapped = 0;
  swapped = (orig & 0xff000000) >> 24;
  swapped += (orig & 0x00ff0000) >> 8;
  swapped += (orig & 0x0000ff00) << 8;
  swapped += (orig & 0x000000ff) << 24;
  *val = swapped;
}