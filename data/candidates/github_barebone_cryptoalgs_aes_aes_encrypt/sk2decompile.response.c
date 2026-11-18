void aes_encrypt(unsigned char *in, unsigned char *out, unsigned char *RoundKey,
                 int bits) {
  unsigned char state[4][4];
  state[0][0] = in[0];
  state[1][0] = in[1];
  state[2][0] = in[2];
  state[3][0] = in[3];
  state[0][1] = in[4];
  state[1][1] = in[5];
  state[2][1] = in[6];
  state[3][1] = in[7];
  state[0][2] = in[8];
  state[1][2] = in[9];
  state[2][2] = in[10];
  state[3][2] = in[11];
  state[0][3] = in[12];
  state[1][3] = in[13];
  state[2][3] = in[14];
  state[3][3] = in[15];
  AddRoundKey(state, RoundKey);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, RoundKey + 4);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, RoundKey + 8);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, RoundKey + 12);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, RoundKey + 16);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, RoundKey + 20);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, RoundKey + 24);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, RoundKey + 28);
  if (bits == 128) {
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, RoundKey + 32);
  } else {
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state, RoundKey + 32);
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state, RoundKey + 36);
    if (bits == 192) {
      SubBytes(state);
      ShiftRows(state);
      AddRoundKey(state, RoundKey + 40);
    } else {
      SubBytes(state);
      ShiftRows(state);
      MixColumns(state);
      AddRoundKey(state, RoundKey + 40);
      SubBytes(state);
      ShiftRows(state);
      MixColumns(state);
      AddRoundKey(state, RoundKey + 44);
      SubBytes(state);
      ShiftRows(state);
      AddRoundKey(state, RoundKey + 48);
    }
  }
  out[0] = state[0][0];
  out[1] = state[1][0];
  out[2] = state[2][0];
  out[3] = state[3][0];
  out[4] = state[0][1];
  out[5] = state[1][1];
  out[6] = state[2][1];
  out[7] = state[3][1];
  out[8] = state[0][2];
  out[9] = state[1][2];
  out[10] = state[2][2];
  out[11] = state[3][2];
  out[12] = state[0][3];
  out[13] = state[1][3];
  out[14] = state[2][3];
  out[15] = state[3][3];
}