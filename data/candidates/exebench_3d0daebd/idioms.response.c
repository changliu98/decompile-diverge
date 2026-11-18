void swt_max(double *sigIn, int sigInLength, double *sigMax)
{
  int i;
  *sigMax = sigIn[0];
  for (i = 1; i < sigInLength; i++)
  {
    if (sigIn[i] > *sigMax)
    {
      *sigMax = sigIn[i];
    }
  }
}