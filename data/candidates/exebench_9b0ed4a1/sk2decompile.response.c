float binary_search(float x, float *xv, int n) {
  int i, l, r;
  float f;
  if (x == xv[0]) return 0.0;
  if (x < xv[0]) return -1.0;
  if (x > xv[n - 1]) return -1.0;
  if (x == xv[n - 1]) return n - 1;
  l = 0;
  r = n - 1;
  while (l <= r) {
    i = (r + l) / 2;
    if (x < xv[i])
      r = i - 1;
    else if (x > xv[i])
      l = i + 1;
    else
      return i;
  }
  f = (x - xv[r]) / (xv[l] - xv[r]);
  return r * (1.0 - f) + l * f;
}