void normalize_angle(double *angle)
{
  while (*angle > 3.14159265358979323846) {
    *angle -= 3.14159265358979323846;
  }
  while (*angle <= -3.14159265358979323846) {
    *angle += 3.14159265358979323846;
  }
}