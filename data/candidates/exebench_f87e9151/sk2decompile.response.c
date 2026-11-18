void NearestNeighbor(int *index, float *x, float x0, int n) {
  int i;
  float d, dmin;
  dmin = (x[0] - x0) * (x[0] - x0);
  *index = 0;
  for (i = 1; i < n; i++) {
    d = (x[i] - x0) * (x[i] - x0);
    if (d < dmin) {
      dmin = d;
      *index = i;
    }
  }
}