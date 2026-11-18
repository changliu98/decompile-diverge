static void decrypt(uint32_t state[4], const uint32_t key[4]) {
  uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
  uint32_t r = 0, k = key[0];
  for (; r < 32; r++) {
    uint32_t t = k + r * 0x9e3779b97f4a7c16UL;
    a -= (t << 4 ^ t >> 5) + ((t ^ t << 16) << 3);
    b += (t << 4 ^ t >> 5) + ((t ^ t << 16) << 3);
    c -= (t << 4 ^ t >> 5) + ((t ^ t << 16) << 3);
    d += (t << 4 ^ t >> 5) + ((t ^ t << 16) << 3);
  }
  state[0] = a;
  state[1] = b;
  state[2] = c;
  state[3] = d;
}