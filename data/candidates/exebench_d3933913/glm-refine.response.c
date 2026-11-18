0

double __cdecl ran0(long *idum)
{
    // 1. De-obfuscate the seed
    long seed = *idum ^ MASK;

    // 2. Park-Miller Linear Congruential Generator step
    // seed = (IA * (seed % IQ)) - (IR * (seed / IQ))
    seed = IA * (seed % IQ) - IR * (seed / IQ);

    // 3. Handle negative results to keep the state within [0, IM - 1]
    if (seed < 0) {
        seed += IM;
    }

    // 4. Normalize to the range [0.0, 1.0)
    double ans = AM * (double)(int)seed;

    // 5. Re-obfuscate the seed before saving it back to memory
    *idum = seed ^ MASK;

    return ans;
}