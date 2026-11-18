void arx_bwd(uchar *state)

{
  uchar *state_local;
  
  state[2] = state[2] << 4 | (byte)((int)(uint)state[2] >> 4);
  state[1] = state[1] ^ state[2];
  state[3] = state[3] ^ *state;
  state[1] = state[1] << 5 | (byte)((int)(uint)state[1] >> 3);
  state[3] = state[3] << 1 | (byte)((int)(uint)state[3] >> 7);
  *state = *state - state[3];
  state[2] = state[2] - state[1];
  *state = *state << 4 | (byte)((int)(uint)*state >> 4);
  state[1] = state[1] ^ *state;
  state[3] = state[3] ^ state[2];
  state[1] = state[1] << 6 | (byte)((int)(uint)state[1] >> 2);
  state[3] = state[3] << 3 | (byte)((int)(uint)state[3] >> 5);
  *state = *state - state[1];
  state[2] = state[2] - state[3];
  return;
}