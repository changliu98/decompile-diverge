double __cdecl randlc(double *x, double a)
{
    // Constants representing powers of 2 and their reciprocals
    const double INV_2_POW_23 = 0.0000001192092895507812;   // 1.0 / 8388608.0
    const double TWO_POW_23   = 8388608.0;                  // 2^23
    const double INV_2_POW_46 = 1.4210854715202e-14;        // 1.0 / 70368744177664.0
    const double TWO_POW_46   = 7.0368744177664e13;         // 2^46

    // Decompose 'a' into high and low 23-bit parts
    double a_hi = (double)(int)(a * INV_2_POW_23);
    double a_lo = a - a_hi * TWO_POW_23;

    // Decompose 'x' into high and low 23-bit parts
    double x_hi = (double)(int)(*x * INV_2_POW_23);
    double x_lo = *x - x_hi * TWO_POW_23;

    // Compute the 46-bit product of 'a' and 'x' using the identity:
    // a * x = (a_hi * 2^23 + a_lo) * (x_hi * 2^23 + x_lo)
    // The intermediate terms are truncated to 23 bits to prevent precision loss
    double t1 = a_hi * x_lo + a_lo * x_hi;
    double t1_trunc = (double)(int)(t1 * INV_2_POW_23);
    
    double t2 = t1_trunc * TWO_POW_23 + a_hi * x_lo + a_lo * x_hi;
    double t2_trunc = (double)(int)(t2 * INV_2_POW_23);
    
    double t3 = (t2_trunc * TWO_POW_23 + t2) * TWO_POW_23 + a_lo * x_lo;

    // Normalize the result to the range [0, 1)
    double t3_trunc = (double)(int)(t3 * INV_2_POW_46);
    *x = t3 - t3_trunc * TWO_POW_46;

    return *x * INV_2_POW_46;
}