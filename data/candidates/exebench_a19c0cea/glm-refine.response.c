99999988

float __cdecl ran1(long *idum)
{
    int j;

    // Initialize the generator if the seed is non-positive or if it hasn't been initialized yet
    if (*idum <= 0 || !ran1_iy)
    {
        // Ensure the seed is positive (fallback to 1 if it was 0)
        *idum = (*idum < 0) ? -*idum : 1;

        // Warm up the generator and fill the shuffle table (ran1_iv)
        for (j = NTAB + 7; j >= 0; --j)
        {
            // Minimal standard generator (Park-Miller): idum = (IA * idum) % IM
            *idum = IA * (*idum % IQ) - IR * (*idum / IQ);
            if (*idum < 0)
                *idum += IM;
            
            // Store the first 32 generated values into the table
            if (j < NTAB)
                ran1_iv[j] = *idum;
        }
        ran1_iy = ran1_iv[0];
    }

    // Standard generation step with Bays-Durham shuffle
    *idum = IA * (*idum % IQ) - IR * (*idum / IQ);
    if (*idum < 0)
        *idum += IM;

    // Use the top bits of ran1_iy to index into the shuffle table
    j = ran1_iy / NDIV;
    ran1_iy = ran1_iv[j];
    ran1_iv[j] = *idum;

    // Scale to the [0, 1) float range and clamp the maximum value
    float temp = AM * (float)ran1_iy;
    return (temp <= RNMX) ? temp : RNMX;
}