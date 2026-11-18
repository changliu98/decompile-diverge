static unsigned int xorshift128plus(unsigned int *state, int high_bit)
{
  while (high_bit >= 32)
  {
    if (state[0] & (1ull << high_bit))
      state[0] ^= (0x1e0ec6d3ull << ((high_bit - 32) & 31));
    --high_bit;
  }
  return state[0];
}