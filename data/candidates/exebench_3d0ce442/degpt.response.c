// Generates a small random value to prevent denormal floating-point numbers.
// Updates the linear congruential generator state using a multiplier and increment.
// Returns a float with a random mantissa in the range [1.0, 2.0) scaled by a small factor,
// ensuring the result is a normalized floating-point number.
float add_denormal_prevention_white_noise(uint *rng_state)
{
  // Update the pseudo-random number generator state using LCG parameters.
  *rng_state = *rng_state * 0x12d687 + 0xd950b;
  
  // Extract a random 7-bit value from the upper bits of the state.
  // Combine it with a fixed exponent to create a normalized float in [1.0, 2.0).
  // This ensures the result is not a denormal number.
  return (float)(*rng_state & 0x7f0000 | 0x1e000000);
}