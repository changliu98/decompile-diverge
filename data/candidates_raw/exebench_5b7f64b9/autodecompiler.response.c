int spline_(double *x, double *y, int n, int ibeg, double ybeg,
            int iend, double yend, double *y2)
{

    int ret_val;


    int k;
    double p, qn, sig, un, u[2000];
# 109 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/ghisvail/nfft/refs/heads/nfft-3.3/3rdparty/cstripack/cstripack.c"
    --y2;
    --y;
    --x;


    if (n > 2000) {
        ret_val = 1;
        return ret_val;
    }
    if (ibeg == 2) {
        y2[2] = 0.;
        p = ybeg;
    } else if (ibeg == 1) {
        y2[2] = -0.5;
        p = (y[3] - y[2]) / (x[3] - x[2]) - ybeg;
    } else {
        ret_val = 2;
        return ret_val;
    }

    for (k = 2; k <= n - 1; ++k) {
        sig = (x[k] - x[k - 1]) / (x[k + 1] - x[k - 1]);
        p = sig * y2[k - 1] + 2.;
        y2[k] = (sig - 1.) / p;
        u[k - 1] = ((y[k + 1] - y[k]) / (x[k + 1] - x[k]) - (y[k] - y[
                k - 1]) / (x[k] - x[k - 1])) * 6. / (x[k + 1] - x[k - 1]) +
                 sig * u[k - 2];

    }

    if (iend == 2) {
        qn = 0.;
        un = yend;
    } else if (iend == 1) {
        qn = 0.5;
        un = (yend - (y[n] - y[n - 1]) / (x[n] - x[n - 1])) * (3. / (x[n] -
                x[n - 1]));
    } else {
        ret_val = 3;
        return ret_val;
    }

    y2[n] = (un + qn * u[n - 2]) / (qn * y2[n - 1] + 1.);
    for (k = n - 1; k >= 1; --k) {
        y2[k] = y2[k] * y2[k + 1] + u[k - 1];

    }
    ret_val = 0;
    return ret_val;
}