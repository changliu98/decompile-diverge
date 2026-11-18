void init_fact(double *fact)
{
  int i;
  fact[0] = 1.;
  for (i = 0; i < 20; i++)
    fact[i + 1] = (double)(i + 1) * fact[i];
}