int INDMAXVAL(float *x, int beg, int end)
{
  int i, imax;

  imax = beg;
  for (i=beg+1; i<=end; i++)
    if (x[i] > x[imax])
      imax = i;
  return(imax);
}