// Generates a pseudo-random number using a linear congruential generator (LCG)
// Updates the seed value pointed to by prandom with the next value in the sequence
// Returns the generated number as a double in the range [0, 1)
double rnd(long *seed)
{
  // Update the seed using LCG formula: next = (current * multiplier + increment) % modulus
  *seed = (*seed * 0x6255 + 0x3619) % 0x10000;
  // Normalize the result to a double in the range [0, 1) by dividing by the modulus (65536)
  return (double)*seed / DAT_00102008;
}