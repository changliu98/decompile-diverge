unsigned long div10quickm(unsigned long *x) {
  unsigned long y, z;
  y = *x;
  z = (y >> 2) + (y >> 1);
  z = z + (z >> 4);
  z = z + (z >> 8);
  z = z + (z >> 16);
  z = z + (z >> 3);
  z = z >> 1;
  z = y - (z << 3);
  *x = z;
  return z - (z << 3);
}