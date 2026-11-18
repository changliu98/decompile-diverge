void SubBytes(unsigned char *state)
{
  state[0] = aes_sbox[state[0] >> 4][state[0] & 0x0f];
  state[1] = aes_sbox[state[1] >> 4][state[1] & 0x0f];
  state[2] = aes_sbox[state[2] >> 4][state[2] & 0x0f];
  state[3] = aes_sbox[state[3] >> 4][state[3] & 0x0f];
  state[4] = aes_sbox[state[4] >> 4][state[4] & 0x0f];
  state[5] = aes_sbox[state[5] >> 4][state[5] & 0x0f];
  state[6] = aes_sbox[state[6] >> 4][state[6] & 0x0f];
  state[7] = aes_sbox[state[7] >> 4][state[7] & 0x0f];
  state[8] = aes_sbox[state[8] >> 4][state[8] & 0x0f];
  state[9] = aes_sbox[state[9] >> 4][state[9] & 0x0f];
  state[10] = aes_sbox[state[10] >> 4][state[10] & 0x0f];
  state[11] = aes_sbox[state[11] >> 4][state[11] & 0x0f];
  state[12] = aes_sbox[state[12] >> 4][state[12] & 0x0f];
  state[13] = aes_sbox[state[13] >> 4][state[13] & 0x0f];
  state[14] = aes_sbox[state[14] >> 4][state[14] & 0x0f];
  state[15] = aes_sbox[state[15] >> 4][state[15] & 0x0f];
}