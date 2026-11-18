// Updates the pseudo-random number pointed to by prandom
// using a linear congruential generator formula.
// The new value is constrained to be within the inclusive range [min, max].
void rnd_between(long *seed, long lower_bound, long upper_bound)
{
  // Apply LCG transformation: next = (current * a + c) % m
  // Then shift the result to fit within the specified [min, max] range.
  *seed = (*seed * 0x6255 + 0x3619) % ((upper_bound + 1) - lower_bound) + lower_bound;
}