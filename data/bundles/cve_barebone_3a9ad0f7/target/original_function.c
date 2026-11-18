static double **AcquireBilateralTLS(const size_t number_threads,
  const size_t width,const size_t height)
{
  double
    **weights;

  ssize_t
    i;

  weights=(double **) AcquireQuantumMemory(number_threads+1,sizeof(*weights));
  if (weights == (double **) NULL)
    return((double **) NULL);
  (void) memset(weights,0,number_threads*sizeof(*weights));
  for (i=0; i <= (ssize_t) number_threads; i++)
  {
    weights[i]=(double *) AcquireQuantumMemory(width,height*sizeof(**weights));
    if (weights[i] == (double *) NULL)
      return(DestroyBilateralTLS(number_threads,weights));
  }
  return(weights);
}