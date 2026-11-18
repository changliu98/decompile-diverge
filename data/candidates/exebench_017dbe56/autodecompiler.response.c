void ZVdotC11(int n, double *x, double *y, double *z)
{
  double d__1, d__2;

  int i__1;
  double r__1, r__2, i__1, i__2;


  int i__, m;
  double r__, i__, xr, xi, yr, yi;
# 69 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/LiangliangNan/PolyFit/refs/heads/main/3rd_lpsolve/shared/myblas.c"
  --y;
  --x;


  r__1 = 0.;
  i__1 = 0.;
  r__2 = r__1;
  i__2 = i__1;
  m = 1;
L10:
  if (m > n) {
    goto L20;
  }
  xr = x[m];
  xi = x[m + 1];
  yr = y[m];
  yi = y[m + 1];
  r__2 = r__2 + xr * yr + xi * yi;
  i__2 = i__2 + xr * yi + xi * yr;
  ++m;
  m += 1;
  goto L10;
L20:
  z[0] = r__2;
  z[1] = i__2;

}