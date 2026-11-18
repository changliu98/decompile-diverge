void ZVdotC11(int n, double *y, double *x, double *sum)
{
    double rsum = 0.0;
    double isum = 0.0;
    int ii, rloc, iloc;

    rloc = 0;
    iloc = 1;
    for (ii = 0; ii < n; ii++) {
        rsum += y[rloc] * x[rloc] + y[iloc] * x[iloc];
        isum += y[rloc] * x[iloc] - y[iloc] * x[rloc];
        rloc += 2;
        iloc += 2;
    }
    sum[0] = rsum;
    sum[1] = isum;
}