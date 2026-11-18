double __cdecl func0(int n)
{
  double nCr = 1.0;
  double res = 1.0;

  for (int r = 1; r <= n; ++r)
  {
    // Iteratively compute the binomial coefficient C(n, r)
    nCr = nCr * (double)(n + 1 - r) / (double)r;
    
    // Accumulate the sum of squares of the binomial coefficients
    res += nCr * nCr;
  }
  
  return res;
}