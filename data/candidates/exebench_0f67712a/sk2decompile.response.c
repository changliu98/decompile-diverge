int transF(int n, int m, float *a, int nout, int mout, float *aout) {
  int i, j;
  if (n != mout || m != nout) return 2000;
  for (j = 0; j < nout; j++) {
    for (i = 0; i < mout; i++) {
      aout[j * mout + i] = a[i * m + j];
    }
  }
  return 0;
}