void swt_max(double *sigIn,int sigInLength,double *sigMax)

{
  int count;
  double *sigMax_local;
  int sigInLength_local;
  double *sigIn_local;
  
  *sigMax = *sigIn;
  for (count = 1; count < sigInLength; count = count + 1) {
    if (*sigMax <= sigIn[count] && sigIn[count] != *sigMax) {
      *sigMax = sigIn[count];
    }
  }
  return;
}