void factorial(double *fact)
{
  int i;

  fact[0] = 1.0;
  for (i=1; i<20; i++) {
    fact[i] = (double)i * fact[i-1];
  }
}