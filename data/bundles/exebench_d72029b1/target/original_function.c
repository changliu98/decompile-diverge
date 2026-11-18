void
test1 (short n, int *x)
{
  short i;

  for (i = 0; i < n; i++)
    {
      i++;
      x[i] = 0;
    }
}