void arcfour_generate_stream(BYTE *state,BYTE *out,size_t len)

{
  BYTE BVar1;
  BYTE t;
  size_t idx;
  int j;
  int i;
  size_t len_local;
  BYTE *out_local;
  BYTE *state_local;
  
  i = 0;
  j = 0;
  for (idx = 0; idx < len; idx = idx + 1) {
    i = (i + 1) % 0x100;
    j = (int)(j + (uint)state[i]) % 0x100;
    BVar1 = state[i];
    state[i] = state[j];
    state[j] = BVar1;
    out[idx] = state[(int)(((uint)state[i] + (uint)state[j]) % 0x100)];
  }
  return;
}