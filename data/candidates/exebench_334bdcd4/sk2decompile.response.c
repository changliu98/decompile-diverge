void ZVdotC31(int n, double *a, double *b, double *c, double *d, double *z) {
  int i, j, k;
  double zr, zi, dr, di, br, bi, ar, ai, br1, bi1, cr, ci;
  zr = zi = dr = di = br = bi = 0.0;
  i = 0;
  j = 0;
  k = 1;
  for (j = 0; j < n; j++) {
    ar = a[i];
    ai = a[k];
    br = b[i];
    bi1 = b[k];
    cr = c[i];
    ci = c[k];
    dr = d[i];
    di = d[k];
    zr += ar * dr + ai * di;
    zi += ar * di - ai * dr;
    br += br * dr + bi1 * di;
    bi += br * di - bi1 * dr;
    zr += cr * dr + ci * di;
    zi += cr * di - ci * dr;
    i += 2;
    k += 2;
  }
  z[0] = zr;
  z[1] = zi;
  z[2] = br;
  z[3] = bi;
  z[4] = zr;
  z[5] = zi;
  return;
}