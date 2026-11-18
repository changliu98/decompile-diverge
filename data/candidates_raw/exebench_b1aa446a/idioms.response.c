char *divmod(long *div, long *mod, char *to, long n)
{
  char *to1 = to;
  if (n < 0)
    {
      *mod = - (n % 10);
      *div = n / - 10;
      *to = '-';
      to++;
    }
  else
    {
      *mod = n % 10;
      *div = n / 10;
    }
  return to1;
}