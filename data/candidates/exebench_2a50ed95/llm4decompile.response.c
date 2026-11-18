void ZVdotC21(int n, double y0[], double y1[], double x0[], double sums[])
{
    double r00 = 0.0;
    double i00 = 0.0;
    double r10 = 0.0;
    double i10 = 0.0;
    int rloc = 0;
    int iloc = 1;
    int ii;
    for (ii = 0; ii < n; ii++) {
        double xr0 = x0[rloc];
        double xi0 = x0[iloc];
        double yr0 = y0[rloc];
        double yi0 = y0[iloc];
        double yr1 = y1[rloc];
        double yi1 = y1[iloc];
        r00 += xr0 * yr0 + xi0 * yi0;
        i00 += xi0 * yr0 - xr0 * yi0;
        r10 += xr0 * yr1 + xi0 * yi1;
        i10 += xi0 * yr1 - xr0 * yi1;
        rloc += 2;
        iloc += 2;
    }
    sums[0] = r00;
    sums[1] = i00;
    sums[2] = r10;
    sums[3] = i10;
}