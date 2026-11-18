void ZVdotC13(int n, double y[], double x0[], double x1[], double x2[],
              double sums[])
{
    double r00, r01, r02, i00, i01, i02;
    double xr0, xr1, xr2, xi0, xi1, xi2;
    double yr0, yi0;
    int rloc, iloc, ii;

    r00 = 0.0;
    i00 = 0.0;
    r01 = 0.0;
    i01 = 0.0;
    r02 = 0.0;
    i02 = 0.0;

    rloc = 0;
    iloc = 1;
    for (ii = 0; ii < n; ii++) {
        yr0 = y[rloc];
        yi0 = y[iloc];

        xr0 = x0[rloc];
        xi0 = x0[iloc];
        r00 += (yr0 * xr0 + yi0 * xi0);
        i00 += (yi0 * xr0 - yr0 * xi0);

        xr1 = x1[rloc];
        xi1 = x1[iloc];
        r01 += (yr0 * xr1 + yi0 * xi1);
        i01 += (yi0 * xr1 - yr0 * xi1);

        xr2 = x2[rloc];
        xi2 = x2[iloc];
        r02 += (yr0 * xr2 + yi0 * xi2);
        i02 += (yi0 * xr2 - yr0 * xi2);

        rloc += 2;
        iloc += 2;
    }

    sums[0] = r00;
    sums[1] = i00;
    sums[2] = r01;
    sums[3] = i01;
    sums[4] = r02;
    sums[5] = i02;
}