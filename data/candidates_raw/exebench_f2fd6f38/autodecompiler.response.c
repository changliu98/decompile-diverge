int FindMax3(float *maxima, int n)
{
  float max=0;
  int i, imax=-1;

  for (i=0; i<17; i++) {
    if (i >= n) continue;
    if (maxima[i] > max) {
      max = maxima[i];
      imax = i;
    }
  }

  if (imax < 0) return -1;

  max *= .10;
  for (i=0; i<17; i++) {
    if (i == imax) continue;
    if (maxima[i] > max) return -1;
  }

  return imax;
}