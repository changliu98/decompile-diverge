void init_factorial(double *factorial)
{
 int i;
 factorial[0] = 1;
 for (i = 0; i < 21; i++)
  factorial[i + 1] = factorial[i] * (i + 1);
}