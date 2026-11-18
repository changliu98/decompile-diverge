void decipher(unsigned long *v, unsigned long *k) {
  unsigned long y, z, sum, e;
  y = v[0];
  z = v[1];
  sum = 0x9e3779b1;
  e = 0x9e3779b1 * 32;
  for (int i = 0; i < 31; i++) {
    z -= (((y << 4) ^ (y >> 5)) + y) ^ (sum + k[(sum >> 11) & 3]);
    sum -= 0x9e3779b1;
    y -= (((z << 4) ^ (z >> 5)) + z) ^ (sum + k[sum & 3]);
  }
  v[0] = y;
  v[1] = z;
}