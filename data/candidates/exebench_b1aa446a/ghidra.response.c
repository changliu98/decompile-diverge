char * get_mod_and_div(long *mod,long *div,char *toa,long n)

{
  long n_local;
  char *toa_local;
  long *div_local;
  long *mod_local;
  
  if (n < 0) {
    *mod = -(n % 10);
    *div = -(n / 10);
    *toa = '-';
    toa_local = toa + 1;
  }
  else {
    *mod = n % 10;
    *div = n / 10;
    toa_local = toa;
  }
  return toa_local;
}