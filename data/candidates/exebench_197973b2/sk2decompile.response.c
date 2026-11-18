void computesizes(int *counts, int n, int *maxsize, int *nsmall) {
  int ntot, ntotmax, maxsizei, i;
  ntot = ntotmax = counts[0];
  maxsizei = (ntot == 0) ? -1 : 0;
  for (i = 1; ntot < *maxsize && *maxsize >= (1 << (i - 1)); i++) {
    if (counts[i] > 0) {
      ntot += counts[i];
      if (ntot >= (1 << (i - 1))) {
        maxsizei = i;
        ntotmax = ntot;
      }
    }
  }
  *nsmall = n - ntotmax;
  *maxsize = (maxsizei == -1) ? 0 : (1 << maxsizei);
}