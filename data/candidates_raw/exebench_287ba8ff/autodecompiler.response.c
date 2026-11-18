void
timestr2(char *b,float *sec,float *frac,int *sign)
{
  int i;

  *sign = b[0] - '0';
  if (*sign < 0 || *sign > 9) return;
  if (*sign == 1) *sec /= 10.0;
  *frac = *frac*10.0 + *sign;
}