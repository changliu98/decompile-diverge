void Decrypt(unsigned char *in, unsigned char *out, unsigned char *key, int keysize)
{
  unsigned char state[4][4];
  unsigned char *inptr = in;
  unsigned char *outptr = out;
  unsigned char *keyptr = key;
  int keysiz = keysize;
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
  if (keysiz > 128)
  {
    if (keysiz > 192)
    {
      AddRoundKey(state, &keyptr[56]);
      InvShiftRows(state);
      InvSubBytes(state);
      AddRoundKey(state, &keyptr[52]);
      InvMixColumns(state);
      InvShiftRows(state);
      InvSubBytes(state);
      AddRoundKey(state, &keyptr[48]);
      InvMixColumns(state);
    }
    else
    {
      AddRoundKey(state, &keyptr[48]);
      InvMixColumns(state);
    }
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, &keyptr[44]);
    InvMixColumns(state);
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, &keyptr[40]);
    InvMixColumns(state);
  }
  else
  {
    AddRoundKey(state, &keyptr[40]);
  }
  InvShiftRows(state);
  InvSubBytes(state);
  AddRoundKey(state, &keyptr[36]);
  InvMixColumns(state);
  InvShiftRows(state);
  InvSubBytes(state);
  AddRoundKey(state, &keyptr[32]);
  InvMixColumns(state);
  InvShiftRows(state);
  InvSubBytes(state);
  AddRoundKey(state, &keyptr[28]);
  InvMixColumns(state);
  InvShiftRows(state);
  InvSubBytes(state);
  AddRoundKey(state, &keyptr[24]);
  InvMixColumns(state);
  InvShiftRows(state);
  InvSubBytes(state);
  AddRoundKey(state, &keyptr[20]);
  InvMixColumns(state);
  InvShiftRows(state);
  InvSubBytes(state);
  AddRoundKey(state, &keyptr[16]);
  InvMixColumns(state);
  InvShiftRows(state);
  InvSubBytes(state);
  AddRoundKey(state, &keyptr[12]);
  InvMixColumns(state);
  InvShiftRows(state);
  InvSubBytes(state);
  AddRoundKey(state, &keyptr[8]);
  InvMixColumns(state);
  InvShiftRows(state);
  InvSubBytes(state);
  AddRoundKey(state, &keyptr[4]);
  InvMixColumns(state);
  InvShiftRows(state);
  InvSubBytes(state);
  AddRoundKey(state, &keyptr[0]);
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