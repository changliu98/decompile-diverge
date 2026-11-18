char *i2hs(unsigned int n, char *ds)
{
 char *tb = "0123456789ABCDEF";
 char ts[32];
 char *tsp = ts, *dsp = ds;

 *tsp = 0;
 while(n > 0) {
  *++tsp = tb[n & 0xf];
  n >>= 4;
 }
 if(!*tsp)
  *++tsp = '0';
 while((*dsp++ = *tsp--));
 return ds;
}