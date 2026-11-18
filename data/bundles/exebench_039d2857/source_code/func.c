
static void
dual_mul( double ar, double ad, double br, double bd, double *cr, double *cd )
{
    *cr = ar*br;
    *cd = ar*bd + ad*br;
}
