float xCorrCoef(float *target, float *regressor, int subl)
{
  float sumX, sumY, sumXY, sumX2, sumY2;
  int i;
  float coef;

  sumX = 0.0;
  sumY = 0.0;
  sumXY = 0.0;
  sumX2 = 0.0;
  sumY2 = 0.0;
  for (i=0; i<subl; i++)
    {
      sumX += regressor[i];
      sumY += target[i];
      sumXY += regressor[i]*target[i];
      sumX2 += regressor[i]*regressor[i];
      sumY2 += target[i]*target[i];
    }
  if (sumXY > 0.0)
    coef = (sumXY*sumXY)/(sumX2*sumY2);
  else
    coef = 0.0;
  return coef;
}