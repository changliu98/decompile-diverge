int clipmaxdouble(double *x,long n,double xmax)
{
  long i;
  int status;

  for(i=0;i<n;i++)
    if(x[i]>xmax)
      x[i]=xmax;

  status=0;
  return status;
}