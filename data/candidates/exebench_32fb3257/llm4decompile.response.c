void ZVdotU21(int n, double y0[], double y1[], double x0[], double sums[])
{
    double r00 = 0.0;
    double i00 = 0.0;
    double r10 = 0.0;
    double i10 = 0.0;
    int rloc = 0;
    int iloc = 1;
    int ii;
    double xr0;
    double xi0;
    double yr0;
    double yi0;
    double yr1;
    double yi1;

    for (ii = 0; ii < n; ii++) {
        xr0 = x0[rloc];
        xi0 = x0[iloc];
        yr0 = y0[rloc];
        yi0 = y0[iloc];
        yr1 = y1[rloc];
        yi1 = y1[iloc];
        r00 += (yr0 * xr0 - yi0 * xi0);
        i00 += (yi0 * xr0 + yr0 * xi0);
        r10 += (yr1 * xr0 - yi1 * xi0);
        i10 += (yi1 * xr0 + yr1 * xi0);
        rloc += 2;
        iloc += 2;
    }
    sums[0] = r00;
    sums[1] = i00;
    sums[2] = r10;
    sums[3] = i10;
}