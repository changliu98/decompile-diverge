int zuchk_(doublecomplex *z, int *nz, double *ascle,
 double *tol)
{

    double d__1, d__2;


    double s, r, t, i;
# 131 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/alishakiba/libflame/refs/heads/master/src/map/lapack2flamec/f2c/c/zuchk.c"
    --nz;


    i = z->i;
    r = z->r;
    s = (d__1 = r, ((d__1) >= 0 ? (d__1) : -(d__1))) + (d__2 = i, ((d__2) >= 0 ? (d__2) : -(d__2)));
    t = (d__1 = r, ((d__1) >= 0 ? (d__1) : -(d__1))) * (d__2 = i, ((d__2) >= 0 ? (d__2) : -(d__2)));







    nz[1] = 0;
    if (s > *ascle) {
 goto L10;
    }
    if (t / *tol < s) {
 nz[1] = 1;
    }
    return 0;

L10:
    return 0;



}