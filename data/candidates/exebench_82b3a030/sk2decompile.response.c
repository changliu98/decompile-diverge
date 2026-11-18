int intwt(double x, double *wt) {
  int i;
  if (x < 1.0) {
    i = 1;
    *wt = x;
  } else {
    i = (int)x;
    *wt = 1.0;
  }
  return i;
}