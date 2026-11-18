// Linear congruential generator for random number generation
// Updates the state using the formula: state = (state * 0x41a7) % 0x7fffffff
// Returns a double-precision floating-point number in the range [0, 1)
// by dividing the updated state by a constant divisor (DAT_00102008)
double linsched_rand(uint *random_state)
{
    // Update the random state using a linear congruential method
    *random_state = (*random_state * 0x41a7) % 0x7fffffff;
    // Normalize the state to a double in the range [0, 1)
    return (double)*random_state / NORMALIZATION_CONSTANT;
}