void __cdecl clamp(double *a_pValue, double a_min, double a_max)
{
  if ( a_min <= *a_pValue )
  {
    if ( *a_pValue > a_max )
      *a_pValue = a_max;
  }
  else
  {
    *a_pValue = a_min;
  }
}