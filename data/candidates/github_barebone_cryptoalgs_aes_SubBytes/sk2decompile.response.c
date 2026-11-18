void SubBytes(unsigned char (*state)[4]) {
  int i;
  for (i = 0; i < 16; i++) {
    (*state)[i] = sbox[((*state)[i] >> 4) * 16 + ((*state)[i] & 0x0F)];
  }
}