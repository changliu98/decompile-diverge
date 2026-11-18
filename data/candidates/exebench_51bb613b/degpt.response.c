// Implements a linear congruential generator (LCG) for generating pseudo-random numbers.
// Uses the same constants as Microsoft's Visual C++ runtime rand_r implementation.
//
// Parameters:
//   nextp - Pointer to the seed/state variable. Must be initialized before first use.
//
// Returns:
//   A pseudo-random integer in the range [0, 32767] (i.e., 0 to 0x7FFF).
//
// Algorithm:
//   next = next * 0x41c64e6d + 0x3039
//   result = (next >> 16) & 0x7FFF
int rand_r(uint *state)
{
    // Update the state using the LCG formula: next = next * a + c
    // where a = 0x41c64e6d and c = 0x3039
    *state = *state * 0x41c64e6d + 0x3039;
    
    // Extract the upper 15 bits of the 32-bit state as the random number
    // Shift right by 16 bits to get the upper half, then mask with 0x7FFF to keep only 15 bits
    return *state >> 0x10 & 0x7fff;
}