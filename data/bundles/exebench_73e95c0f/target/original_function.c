void clamp(double * a_pValue, double a_min, double a_max)
{
 if(*a_pValue < a_min)
  *a_pValue = a_min;
 else if(*a_pValue > a_max)
  *a_pValue = a_max;
}