void AES128Encrypt(unsigned char *in, unsigned char *out, unsigned char *key, int keysize)
{
  unsigned char state[4][4];
  unsigned char *inptr = in;
  unsigned char *outptr = out;
  unsigned char *keyptr = key;
  int keysizein = keysize;
  state[0][0] = inptr[0];
  state[1][0] = inptr[1];
  state[2][0] = inptr[2];
  state[3][0] = inptr[3];
  state[0][1] = inptr[4];
  state[1][1] = inptr[5];
  state[2][1] = inptr[6];
  state[3][1] = inptr[7];
  state[0][2] = inptr[8];
  state[1][2] = inptr[9];
  state[2][2] = inptr[10];
  state[3][2] = inptr[11];
  state[0][3] = inptr[12];
  state[1][3] = inptr[13];
  state[2][3] = inptr[14];
  state[3][3] = inptr[15];
  AddRoundKey(state, keyptr);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keyptr + 4 * 4);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keyptr + 4 * 4 + 4 * 4);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
  SubBytes(state);
  ShiftRows(state);
  AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
  if (keysizein == 128)
  {
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
  }
  else
  {
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
    if (keysizein == 192)
    {
      SubBytes(state);
      ShiftRows(state);
      AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
    }
    else
    {
      SubBytes(state);
      ShiftRows(state);
      MixColumns(state);
      AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
      SubBytes(state);
      ShiftRows(state);
      MixColumns(state);
      AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
      SubBytes(state);
      ShiftRows(state);
      AddRoundKey(state, keyptr + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4 + 4 * 4);
    }
  }
  outptr[0] = state[0][0];
  outptr[1] = state[1][0];
  outptr[2] = state[2][0];
  outptr[3] = state[3][0];
  outptr[4] = state[0][1];
  outptr[5] = state[1][1];
  outptr[6] = state[2][1];
  outptr[7] = state[3][1];
  outptr[8] = state[0][2];
  outptr[9] = state[1][2];
  outptr[10] = state[2][2];
  outptr[11] = state[3][2];
  outptr[12] = state[0][3];
  outptr[13] = state[1][3];
  outptr[14] = state[2][3];
  outptr[15] = state[3][3];
}