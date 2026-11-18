void normalize_angle(double *angle)
{
 while (*angle > 2*3.14159265) *angle -= 2*3.14159265;
 while (*angle < 0) *angle += 2*3.14159265;
}