static double func0(double x)
{
  double sqrt_5 = sqrt(5);
  double sqrt_25 = sqrt(sqrt_5 * (sqrt_5 + sqrt_5 + sqrt_5));
  return (sqrt_25 * pow(x, 2)) / 4;
}