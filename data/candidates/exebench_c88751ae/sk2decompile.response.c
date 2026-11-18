int hmsra(int h, int m, float s, double *ra) {
  *ra = (double)h + (double)m / 60.0 + (double)s / 3600.0;
  *ra *= 15.0;
  if (*ra < 0.0 || *ra > 360.0) return 1;
  return 0;
}