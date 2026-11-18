void arx_bwd(unsigned char *state)
{
  state[2] = (state[2] << 4) | (state[2] >> 4);
  state[1] ^= state[2];
  state[3] ^= state[0];
  state[1] = (state[1] << 3) | (state[1] >> 3);
  state[3] = (state[3] << 7) | (state[3] >> 7);
  state[0] ^= state[3];
  state[2] ^= state[1];
  state[0] = (state[0] << 4) | (state[0] >> 4);
  state[1] ^= state[0];
  state[3] ^= state[2];
  state[1] = (state[1] << 6) | (state[1] >> 2);
  state[3] = (state[3] << 8) | (state[3] >> 5);
  state[0] ^= state[1];
  state[2] ^= state[3];
}