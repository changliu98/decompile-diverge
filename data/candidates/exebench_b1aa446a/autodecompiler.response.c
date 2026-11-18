char *get_mod_and_div(long long n, long long base, char *res, long long div)
{
 if (div < 0)
 {
  *res = '-';
  res++;
  *n = -1 * (div % base);
  *base = -1 * (div / base);
 }
 else
 {
  *n = div % base;
  *base = div / base;
 }
 return (res);
}