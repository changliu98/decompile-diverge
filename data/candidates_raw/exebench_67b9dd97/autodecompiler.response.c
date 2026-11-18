float innerprod(float *a, float *b, int n)
{
  int i=0;
  float sum=0;

  while(1)
  {
    if(i<n)
    {
      sum+=(*a++)*(*b++);
      i++;
    }
    else
      return sum;
  }
}