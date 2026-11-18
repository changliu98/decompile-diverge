void __cdecl add_angles(double cos_a, double sin_a, double cos_b, double sin_b, double *cos_sum, double *sin_sum)
{
  *cos_sum = cos_a * cos_b - sin_a * sin_b;
  *sin_sum = sin_a * cos_b + cos_a * sin_b;
}