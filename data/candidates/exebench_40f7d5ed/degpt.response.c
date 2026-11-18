// Linear congruential random number generator
// Updates the seed value using a multiplicative congruential method
// Ensures the seed remains positive by adding 0x7fffffff if negative
// Returns a normalized double value in the range [0, 1)
double ran0bis(long *seed)
{
    // Update seed using LCG formula: idum = (a * idum) mod m
    // Using optimized integer arithmetic to avoid overflow
    *seed = *seed * 0x41a7 + (*seed / 0x1f31d) * -0x7fffffff;
    
    // Correct negative result to keep seed in valid range [0, 0x7fffffff]
    if (*seed < 0) {
        *seed = *seed + 0x7fffffff;
    }
    
    // Normalize the integer seed to a double in [0, 1) range
    return normalization_factor * (double)*seed;
}