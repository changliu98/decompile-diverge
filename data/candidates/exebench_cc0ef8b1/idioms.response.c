float xCorrCoef(float *target, float *regressor, int subl)
{
  int i;
  float rsum = 0.;
  float rsum2 = 0.;
  for (i = 0; i < subl; i++)
  {
    rsum += regressor[i] * target[i];
    rsum2 += regressor[i] * regressor[i];
  }
  if (rsum > 0.)
  {
    return rsum * rsum / rsum2;
  }
  else
  {
    return 0.;
  }
}