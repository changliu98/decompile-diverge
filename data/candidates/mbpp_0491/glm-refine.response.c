double __cdecl func0(double a, int n, double r)
{
  // Geometric Series Sum: S_n = a * (1 - r^n) / (1 - r)
  return a * (1.0 - pow(r, (double)n)) / (1.0 - r);
}