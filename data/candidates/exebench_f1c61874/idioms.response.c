static void squeeze(unsigned int *state)
{
  unsigned int carry = 0;
  unsigned int i;
  for (i = 0; i < 31; i++) {
    carry += state[i];
    state[i] = carry & 0xff;
    carry >>= 8;
  }
  carry += state[31];
  state[31] = carry & 0x7f;
  carry = (carry >> 7) * 19;
  for (i = 0; i < 31; i++) {
    carry += state[i];
    state[i] = carry & 0xff;
    carry >>= 8;
  }
  state[31] += carry;
}