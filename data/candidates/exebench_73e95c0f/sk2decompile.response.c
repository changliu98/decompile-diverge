void clamp(double *x, double min, double max) {
  if (*x < min)
    *x = min;
  else if (*x > max)
    *x = max;
}