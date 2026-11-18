float __cdecl add_denormal_prevention_white_noise(unsigned int *rand_state)
{
  // Advance the Linear Congruential Generator (LCG) state
  *rand_state = 1234567 * *rand_state + 890123;

  // Construct a small floating-point number in the range [2^-7, 2^-6)
  // by masking the middle bits of the random state and forcing the 
  // exponent to a fixed, small value.
  unsigned int noise_bits = (*rand_state & 0x007F0000) | 0x1E000000;

  // Reinterpret the constructed integer bits as a float
  return *(float *)&noise_bits;
}