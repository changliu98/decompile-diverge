void normalize_angle(double *angle)
{

 while (*angle > (360.0 * (3.14159265) / 180.0))
  *angle -= (360.0 * (3.14159265) / 180.0);
 while (*angle < 0)
  *angle += (360.0 * (3.14159265) / 180.0);
}