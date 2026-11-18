static long long fact(int n)
{
  long long fact = 1;
  long long bfact = 1;
  int i;
  for (i = 1; i <= n; i++) {
    fact *= i;
    bfact *= fact;
  }
  return bfact;
}