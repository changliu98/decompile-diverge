void InvSubBytes(BYTE (*state) [4])

{
  BYTE (*state_local) [4];
  
  (*state)[0] = aes_invsbox[(int)(uint)(*state)[0] >> 4][(int)((*state)[0] & 0xf)];
  (*state)[1] = aes_invsbox[(int)(uint)(*state)[1] >> 4][(int)((*state)[1] & 0xf)];
  (*state)[2] = aes_invsbox[(int)(uint)(*state)[2] >> 4][(int)((*state)[2] & 0xf)];
  (*state)[3] = aes_invsbox[(int)(uint)(*state)[3] >> 4][(int)((*state)[3] & 0xf)];
  state[1][0] = aes_invsbox[(int)(uint)state[1][0] >> 4][(int)(state[1][0] & 0xf)];
  state[1][1] = aes_invsbox[(int)(uint)state[1][1] >> 4][(int)(state[1][1] & 0xf)];
  state[1][2] = aes_invsbox[(int)(uint)state[1][2] >> 4][(int)(state[1][2] & 0xf)];
  state[1][3] = aes_invsbox[(int)(uint)state[1][3] >> 4][(int)(state[1][3] & 0xf)];
  state[2][0] = aes_invsbox[(int)(uint)state[2][0] >> 4][(int)(state[2][0] & 0xf)];
  state[2][1] = aes_invsbox[(int)(uint)state[2][1] >> 4][(int)(state[2][1] & 0xf)];
  state[2][2] = aes_invsbox[(int)(uint)state[2][2] >> 4][(int)(state[2][2] & 0xf)];
  state[2][3] = aes_invsbox[(int)(uint)state[2][3] >> 4][(int)(state[2][3] & 0xf)];
  state[3][0] = aes_invsbox[(int)(uint)state[3][0] >> 4][(int)(state[3][0] & 0xf)];
  state[3][1] = aes_invsbox[(int)(uint)state[3][1] >> 4][(int)(state[3][1] & 0xf)];
  state[3][2] = aes_invsbox[(int)(uint)state[3][2] >> 4][(int)(state[3][2] & 0xf)];
  state[3][3] = aes_invsbox[(int)(uint)state[3][3] >> 4][(int)(state[3][3] & 0xf)];
  return;
}