int dspline(double *x, double *y, int n, int if1, double cond1, int ifn,
 double condn, double *y2)
{

    int i__1, i__2;


    double d__1, d__2;


    int i__, k;
    double p, qn, sig, un, u[2000];
# 291 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/CAAP/Lua/refs/heads/master/src/lcdf/dcdflib.c"
    --y2;
    --y;
    --x;


    if (n > 2000) {
 return 1;
    }

    if (if1 == 2) {
 i__1 = 1;
 y2[1] = 0.;
 u[1] = cond1;
    } else if (if1 == 1) {
 i__1 = 1;
 y2[1] = -.5;
 u[1] = (3. / (x[2] - x[1])) * ((y[2] - y[1]) / (x[2] - x[1]) - cond1);
    } else {
 return 2;
    }

    i__1 = n - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
 sig = (x[i__] - x[i__ - 1]) / (x[i__ + 1] - x[i__ - 1]);
 p = sig * y2[i__ - 1] + 2.;
 y2[i__] = (sig - 1.) / p;
 u[i__] = (6. * ((y[i__ + 1] - y[i__]) / (x[i__ + 1] - x[i__]) - (y[i__] -
  y[i__ - 1]) / (x[i__] - x[i__ - 1])) / (x[i__ + 1] - x[i__ - 1]) -
  sig * u[i__ - 1]) / p;

    }

    if (ifn == 2) {
 qn = 0.;
 un = condn;
    } else if (ifn == 1) {
 qn = .5;
 un = (3. / (x[n] - x[n - 1])) * (condn - (y[n] - y[n - 1]) / (x[n] -
  x[n - 1]));
    } else {
 return 3;
    }

    y2[n] = (un - qn * u[n - 1]) / (qn * y2[n - 1] + 1.);
    i__1 = n;
    for (k = 1; k <= i__1; ++k) {
 i__ = n - k;
 y2[i__] = y2[i__] * y2[n] + u[i__];

    }

    return 0;
}