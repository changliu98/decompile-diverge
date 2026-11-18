void standardize(int n, double min1[3], double max1[3], double step1[3],
  double min2[3], double max2[3], double step2[3])
{
  int i;
  for(i=0; i<3; i++)
    if(i < n)
      {
 min1[i] = min2[i];
 max1[i] = max2[i];
 step1[i] = step2[i];
      }
    else
      {
 min1[i] = 0.;
 max1[i] = 1.;
 step1[i] = 1.;
      }
}