double __cdecl func0(int num)
{
  double num_cubed = pow((double)num, 3.0);
  double sqrt_2 = sqrt(2.0);
  return round(100.0 * (num_cubed / (6.0 * sqrt_2))) / 100.0;
}