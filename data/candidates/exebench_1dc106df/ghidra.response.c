char * i2hs(uint n,char *ds)

{
  char cVar1;
  char *dsp;
  char *tsp;
  char ts [32];
  char *tb;
  char *ds_local;
  uint n_local;
  
  ts[0] = '\0';
  tsp = ts;
  for (n_local = n; n_local != 0; n_local = n_local >> 4) {
    tsp[1] = "0123456789ABCDEF"[n_local & 0xf];
    tsp = tsp + 1;
  }
  dsp = ds;
  if (*tsp == '\0') {
    tsp[1] = '0';
    dsp = ds;
    tsp = tsp + 1;
  }
  do {
    cVar1 = *tsp;
    *dsp = cVar1;
    dsp = dsp + 1;
    tsp = tsp + -1;
  } while (cVar1 != '\0');
  return ds;
}