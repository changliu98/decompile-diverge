void dec2bin(int n,char *rbn)

{
  char *rbn_local;
  int n_local;
  
  rbn_local = rbn;
  for (n_local = n; 0 < n_local; n_local = n_local >> 1) {
    if ((n_local & 1U) == 0) {
      *rbn_local = '0';
    }
    else {
      *rbn_local = '1';
    }
    rbn_local = rbn_local + 1;
  }
  return;
}