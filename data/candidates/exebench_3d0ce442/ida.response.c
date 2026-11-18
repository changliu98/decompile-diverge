float __cdecl add_denormal_prevention_white_noise(unsigned int *rand_state)
{
  float result; // xmm0_4

  *rand_state = 1234567 * *rand_state + 890123;
  LODWORD(result) = *rand_state & 0x7F0000 | 0x1E000000;
  return result;
}