void normalize_angle(double *angle)
{
  while (*angle > 2*3.14159265358979323846)
    *angle -= 2*3.14159265358979323846;
  while (*angle < 0)
    *angle += 2*3.14159265358979323846;
}