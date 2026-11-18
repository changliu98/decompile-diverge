void normalize_angle(double *angle) {
  while (*angle > 6.2831853) {
    *angle -= 6.2831853;
  }
  while (*angle < 0) {
    *angle += 6.2831853;
  }
}