void clamp(double *pValue, double min, double max)
{
  if (*pValue < min)
    *pValue = min;
  else if (*pValue > max)
    *pValue = max;
}