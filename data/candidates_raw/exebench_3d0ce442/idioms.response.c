static float getrandf(unsigned int *rand_state)
{
  *rand_state = *rand_state * 1234567 + 890123;
  return (float)(*rand_state & 0x7ff00000 | 0x10000000);
}