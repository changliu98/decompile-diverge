double **AcquireBilateralTLS(unsigned long num_threads,
  unsigned long width, unsigned long height)
{
  double **weight_cache;
  long i;

  weight_cache=(double **) AcquireQuantumMemory((size_t) (num_threads+1),
    sizeof(double *));
  if (weight_cache == (double **) NULL)
    return(NULL);

  memset(weight_cache,0,(size_t) (num_threads+1)*sizeof(double *));

  for (i=0; i <= (long) num_threads; i++)
  {
    weight_cache[i]=(double *) AcquireQuantumMemory((size_t) width,
      sizeof(double *)*height);
    if (weight_cache[i] == (double *) NULL)
      return(DestroyBilateralTLS(num_threads,weight_cache));
  }

  return(weight_cache);
}