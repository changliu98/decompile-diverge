void encode_vector(char *str, int x, int y) {
  str[0] = (y >> 5) + 32;
  str[1] = (y & 31) + 96;
  str[2] = (x >> 5) + 32;
  str[3] = (x & 31) + 64;
  str[4] = 0;
}