
static char *get_mod_and_div(long *mod, long *div, char *toa, long n)
{
 if (n < 0)
 {
  *mod = (n % 10) * -1;
  *div = (n / 10) * -1;
  *toa = '-';
  toa++;
 }
 else
 {
  *mod = n % 10;
  *div = n / 10;
 }
 return (toa);
}
