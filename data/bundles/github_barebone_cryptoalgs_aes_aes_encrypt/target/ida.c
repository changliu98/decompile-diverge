void __cdecl aes_encrypt(const BYTE *in, BYTE *out, const WORD *key, int keysize)
{
  BYTE state[4][4]; // [rsp+0h] [rbp-30h] BYREF
  int keysizea; // [rsp+14h] [rbp-1Ch]
  const WORD *keya; // [rsp+18h] [rbp-18h]
  BYTE *outa; // [rsp+20h] [rbp-10h]
  const BYTE *ina; // [rsp+28h] [rbp-8h]

  ina = in;
  outa = out;
  keya = key;
  keysizea = keysize;
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
  state[3][2] = in[11];
  state[0][3] = in[12];
  state[1][3] = in[13];
  state[2][3] = in[14];
  state[3][3] = in[15];
  AddRoundKey(state, key);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keya + 4);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keya + 8);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keya + 12);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keya + 16);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keya + 20);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keya + 24);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keya + 28);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keya + 32);
  SubBytes(state);
  ShiftRows(state);
  MixColumns(state);
  AddRoundKey(state, keya + 36);
  if ( keysizea == 128 )
  {
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, keya + 40);
  }
  else
  {
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state, keya + 40);
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state, keya + 44);
    if ( keysizea == 192 )
    {
      SubBytes(state);
      ShiftRows(state);
      AddRoundKey(state, keya + 48);
    }
    else
    {
      SubBytes(state);
      ShiftRows(state);
      MixColumns(state);
      AddRoundKey(state, keya + 48);
      SubBytes(state);
      ShiftRows(state);
      MixColumns(state);
      AddRoundKey(state, keya + 52);
      SubBytes(state);
      ShiftRows(state);
      AddRoundKey(state, keya + 56);
    }
  }
  *outa = state[0][0];
  outa[1] = state[1][0];
  outa[2] = state[2][0];
  outa[3] = state[3][0];
  outa[4] = state[0][1];
  outa[5] = state[1][1];
  outa[6] = state[2][1];
  outa[7] = state[3][1];
  outa[8] = state[0][2];
  outa[9] = state[1][2];
  outa[10] = state[2][2];
  outa[11] = state[3][2];
  outa[12] = state[0][3];
  outa[13] = state[1][3];
  outa[14] = state[2][3];
  outa[15] = state[3][3];
}