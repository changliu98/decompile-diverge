
void swt_max(double *sigIn, int sigInLength, double *sigMax)
 {
  int count;

  *sigMax = sigIn[0];
  for(count=1;count<sigInLength;count++)
  {
         if (sigIn[count] > *sigMax)
    *sigMax = sigIn[count];
  }
  return;
 }
