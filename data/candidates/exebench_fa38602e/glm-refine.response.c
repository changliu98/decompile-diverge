int __cdecl params_exactN(
        double *H0,
        double *L0,
        double *xc,
        double *a,
        double *Hela,
        double *k,
        double *H_xc,
        double *T_xc)
{
    // 1. Initialize base parameters
    *H0 = 3000.0;
    *L0 = 500000.0;
    *xc = 0.9 * *L0;            // 450000.0
    *a = 9.506629384623839e-11;

    // 2. Calculate intermediate and dependent values
    *Hela = *H0 / 1.5;          // 2000.0
    *k = 9.0 * *Hela / (*a * *L0 * *L0);

    // 3. Compute values at the specific point 'xc'
    double ratio = *xc / *L0;   // 0.9
    *H_xc = *H0 * (1.0 - ratio * ratio);
    *T_xc = 512.3530155642026 * *H_xc * *H_xc;

    return 0;
}