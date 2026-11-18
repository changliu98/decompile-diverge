void MvmntMatMult(int n, double *a, double *b, double *c,
                  double *d, double *prod)
{
    int i, j;
    double ar0, ai0, ar1, ai1, ar2, ai2;
    double xr0, xi0, xr1, xi1, xr2, xi2;
    double pr0, pi0, pr1, pi1, pr2, pi2;

    pr0 = pr1 = pr2 = pi0 = pi1 = pi2 = 0.0;

    i = 0;
    j = 1;

    while (1) {
        if (i >= n) break;

        ar0 = a[i];
        ai0 = a[j];

        ar1 = b[i];
        ai1 = b[j];

        ar2 = c[i];
        ai2 = c[j];

        xr0 = d[i];
        xi0 = d[j];

        pr0 += ar0 * xr0 + ai0 * xi0;
        pi0 += ar0 * xi0 + ai0 * xr0;

        pr1 += ar1 * xr0 + ai1 * xi0;
        pi1 += ar1 * xi0 + ai1 * xr0;

        pr2 += ar2 * xr0 + ai2 * xi0;
        pi2 += ar2 * xi0 + ai2 * xr0;

        i += 2;
        j += 2;
    }

    prod[0] = pr0;
    prod[1] = pi0;
    prod[2] = pr1;
    prod[3] = pi1;
    prod[4] = pr2;
    prod[5] = pi2;
}