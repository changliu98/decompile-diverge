double __cdecl ran0bis(long *idum)
{
    long seed = *idum;
    const long IA = 16807;
    const long IM = 0x7FFFFFFF; // 2147483647
    const long IQ = 127773;
    const long IR = 2836;
    const double SCALE = 4.656612875245797e-10; // 1.0 / 2147483647.0

    // Park-Miller linear congruential generator
    *idum = IA * (seed % IQ) - IR * (seed / IQ);
    
    // Ensure the seed is positive
    if (*idum < 0)
        *idum += IM;
        
    // Normalize to the range [0.0, 1.0)
    return SCALE * (double)(int)*idum;
}