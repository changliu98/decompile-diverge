void clamp(double *a_pValue,double a_min,double a_max)

{
  double a_max_local;
  double a_min_local;
  double *a_pValue_local;
  
  if (a_min <= *a_pValue) {
    if (a_max < *a_pValue) {
      *a_pValue = a_max;
    }
  }
  else {
    *a_pValue = a_min;
  }
  return;
}