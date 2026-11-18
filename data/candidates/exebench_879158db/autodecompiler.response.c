unsigned long xorshf96(unsigned long *state1, unsigned long *state2, unsigned long *state3) {
  unsigned long x, y;

  x = *state1;
  y = *state2;

  *state1 = *state1 ^ (*state1 << 16);
  *state1 ^= *state1 >> 5;
  *state1 ^= *state1 << 1;

  x = *state1 ^ x ^ *state2;

  *state1 = *state2;
  *state2 = *state3;
  *state3 = x ^ *state1 ^ *state2;

  return *state3;
}