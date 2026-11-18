void aes_encrypt(BYTE *in,BYTE *out,WORD *key,int keysize)

{
  BYTE state [4] [4];
  int keysize_local;
  WORD *key_local;
  BYTE *out_local;
  BYTE *in_local;
  
  state[0][0] = *in;
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
  state[3][2] = in[0xb];
  state[0][3] = in[0xc];
  state[1][3] = in[0xd];
  state[2][3] = in[0xe];
  state[3][3] = in[0xf];
  AddRoundKey(state,key);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state,key + 4);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state,key + 8);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state,key + 0xc);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state,key + 0x10);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state,key + 0x14);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state,key + 0x18);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state,key + 0x1c);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state,key + 0x20);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state,key + 0x24);
  if (keysize == 0x80) {
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state,key + 0x28);
  }
  else {
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state,key + 0x28);
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state,key + 0x2c);
    if (keysize == 0xc0) {
      SubBytes(state);
      ShiftRows(state);
      AddRoundKey(state,key + 0x30);
    }
    else {
      SubBytes(state);
      ShiftRows(state);
      MixColumns(state);
      AddRoundKey(state,key + 0x30);
      SubBytes(state);
      ShiftRows(state);
      MixColumns(state);
      AddRoundKey(state,key + 0x34);
      SubBytes(state);
      ShiftRows(state);
      AddRoundKey(state,key + 0x38);
    }
  }
  *out = state[0][0];
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
  out[0xb] = state[3][2];
  out[0xc] = state[0][3];
  out[0xd] = state[1][3];
  out[0xe] = state[2][3];
  out[0xf] = state[3][3];
  return;
}