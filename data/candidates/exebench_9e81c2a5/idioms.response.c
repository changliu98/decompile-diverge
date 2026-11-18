void decipher(unsigned long *state, unsigned long *seed)
{
  unsigned long s0 = state[0];
  unsigned long s1 = state[1];
  unsigned long a = 0x1328b7bd67ull;
  unsigned long i;
  for (i = 0; i < 31; i++)
  {
    s1 -= (a + s0) ^ (s0 << 5 ^ s0);
    a -= 0x9e370001;
    s0 -= (a + s1) ^ (s1 << 5 ^ s1);
  }
  state[0] = s0;
  state[1] = s1;
}