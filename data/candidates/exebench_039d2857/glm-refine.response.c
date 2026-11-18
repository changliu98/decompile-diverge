void dual_mul(double ar, double ad, double br, double bd, double *cr, double *cd)
{
    // Real part
    *cr = ar * br;

    // Dual part
    *cd = (ar * bd) + (ad * br);
}