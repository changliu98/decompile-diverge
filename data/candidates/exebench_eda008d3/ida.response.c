void __cdecl arx_bwd(unsigned __int8 *state)
{
  state[2] = ((int)state[2] >> 4) | (16 * state[2]);
  state[1] ^= state[2];
  state[3] ^= *state;
  state[1] = ((int)state[1] >> 3) | (32 * state[1]);
  state[3] = ((int)state[3] >> 7) | (2 * state[3]);
  *state -= state[3];
  state[2] -= state[1];
  *state = ((int)*state >> 4) | (16 * *state);
  state[1] ^= *state;
  state[3] ^= state[2];
  state[1] = ((int)state[1] >> 2) | (state[1] << 6);
  state[3] = ((int)state[3] >> 5) | (8 * state[3]);
  *state -= state[1];
  state[2] -= state[3];
}