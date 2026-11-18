double __cdecl HTS_rnd(unsigned __int64 *next)
{
  // 1. Advance the internal state of the Linear Congruential Generator (LCG)
  // Note: The multiplication implicitly wraps around on 64-bit overflow.
  *next = 1103515245ULL * *next + 12345ULL;

  // 2. Extract bits 16 through 30 (a 15-bit integer) from the 64-bit state
  // IDA's pointer arithmetic translates to a bitwise shift and cast.
  unsigned int shifted_state = (unsigned int)(*next >> 16);
  unsigned int rand_val = shifted_state & 0x7FFF;

  // 3. Normalize the 15-bit integer to a double in the range [0.0, 1.0]
  return (double)rand_val / 32767.0;
}