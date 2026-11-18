static double area(int n, double radius)
{
  return (double) n * (radius * radius) / (4 * tan(3.14159265358979323846 / (double) n));
}