void
relax_ata(int n, double *A, double *B,
    double *C, double *D, double *E,
    double *G)
{
 double ar0, ai0, ar1, ai1;
 double xr0, xi0, xr1, xi1, xr2, xi2;
 double tr0, ti0, tr1, ti1, tr2, ti2;
 int i, j, k;

 tr0 = tr1 = tr2 = ti0 = ti1 = ti2 = 0.0;
 i = 0;
 j = 0;
 k = 1;
 while (1) {
  if (i >= n) break;
  ar0 = A[j];
  ai0 = A[k];
  ar1 = B[j];
  ai1 = B[k];
  xr0 = C[j];
  xi0 = C[k];
  xr1 = D[j];
  xi1 = D[k];
  xr2 = E[j];
  xi2 = E[k];

  tr0 += ar0*xr0 + ai0*xi0;
  ti0 += ar0*xi0 + ai0*xr0;
  tr1 += ar0*xr1 + ai0*xi1;
  ti1 += ar0*xi1 + ai0*xr1;
  tr2 += ar0*xr2 + ai0*xi2;
  ti2 += ar0*xi2 + ai0*xr2;

  tr0 += ar1*xr0 + ai1*xi0;
  ti0 += ar1*xi0 + ai1*xr0;
  tr1 += ar1*xr1 + ai1*xi1;
  ti1 += ar1*xi1 + ai1*xr1;
  tr2 += ar1*xr2 + ai1*xi2;
  ti2 += ar1*xi2 + ai1*xr2;
  i++;
  j += 2;
  k += 2;
 }
 G[0] = tr0;
 G[1] = ti0;
 G[2] = tr1;
 G[3] = ti1;
 G[4] = tr2;
 G[5] = ti2;
}