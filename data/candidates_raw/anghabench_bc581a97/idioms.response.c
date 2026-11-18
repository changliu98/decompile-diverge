static double log10(double N)
{
  double logN = 1.0;
  double x = 10.0;
  while (x < N) {
    logN += 1.0;
    x *= 10.0;
  }
  return logN;
}