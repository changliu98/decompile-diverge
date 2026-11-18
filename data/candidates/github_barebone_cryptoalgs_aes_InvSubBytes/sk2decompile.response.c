void InvSubBytes(unsigned char **state) {
  (*state)[0] = inv_sbox[((*state)[0] >> 4) * 16 + ((*state)[0] & 0x0F)];
  (*state)[1] = inv_sbox[((*state)[1] >> 4) * 16 + ((*state)[1] & 0x0F)];
  (*state)[2] = inv_sbox[((*state)[2] >> 4) * 16 + ((*state)[2] & 0x0F)];
  (*state)[3] = inv_sbox[((*state)[3] >> 4) * 16 + ((*state)[3] & 0x0F)];
  (*state)[4] = inv_sbox[((*state)[4] >> 4) * 16 + ((*state)[4] & 0x0F)];
  (*state)[5] = inv_sbox[((*state)[5] >> 4) * 16 + ((*state)[5] & 0x0F)];
  (*state)[6] = inv_sbox[((*state)[6] >> 4) * 16 + ((*state)[6] & 0x0F)];
  (*state)[7] = inv_sbox[((*state)[7] >> 4) * 16 + ((*state)[7] & 0x0F)];
  (*state)[8] = inv_sbox[((*state)[8] >> 4) * 16 + ((*state)[8] & 0x0F)];
  (*state)[9] = inv_sbox[((*state)[9] >> 4) * 16 + ((*state)[9] & 0x0F)];
  (*state)[10] = inv_sbox[((*state)[10] >> 4) * 16 + ((*state)[10] & 0x0F)];
  (*state)[11] = inv_sbox[((*state)[11] >> 4) * 16 + ((*state)[11] & 0x0F)];
  (*state)[12] = inv_sbox[((*state)[12] >> 4) * 16 + ((*state)[12] & 0x0F)];
  (*state)[13] = inv_sbox[((*state)[13] >> 4) * 16 + ((*state)[13] & 0x0F)];
  (*state)[14] = inv_sbox[((*state)[14] >> 4) * 16 + ((*state)[14] & 0x0F)];
  (*state)[15] = inv_sbox[((*state)[15] >> 4) * 16 + ((*state)[15] & 0x0F)];
}