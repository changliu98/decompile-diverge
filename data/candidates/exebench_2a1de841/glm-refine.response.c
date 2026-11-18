define MINSTD_RAND_MAX 2147483647

double __cdecl linsched_rand(unsigned int *const state)
{
    int product, quotient, remainder, qmod;
    int rand; 

    product = MINSTD_MULT * *state;
    
    // Fast 32-bit division by 3 using multiply-high and shifts
    quotient = (3 * (unsigned __int64)product) >> 32;
    remainder = (product - quotient) >> 1;
    qmod = (quotient + remainder) >> 30;

    // Compute the new state: (16807 * state) mod 2147483647
    rand = product - (MINSTD_RAND_MAX * qmod);
    *state = rand;

    // Normalize to a double in the range [0, 1)
    return (double)rand / (double)MINSTD_RAND_MAX;
}