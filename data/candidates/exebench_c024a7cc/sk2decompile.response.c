void pn_diag_SD_contr(int n, double *x, double *y, double *d) {
  double dd;
  do {
    dd = *d++;
    *y++ += dd * *x++;
  } while (--n);
}