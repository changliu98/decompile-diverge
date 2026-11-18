int __cdecl func0(int n)
{
  if (n < 0)
    return 0;
  if (n <= 1)
    return 1;

  // Stirling's approximation for the number of digits in n!
  // log10(n!) ≈ n * log10(n / e) + log10(2 * pi * n) / 2
  double term1 = log10((double)n / M_E);
  double term2 = log10(2.0 * M_PI * (double)n);
  
  return (int)floor((double)n * term1 + term2 / 2.0) + 1;
}