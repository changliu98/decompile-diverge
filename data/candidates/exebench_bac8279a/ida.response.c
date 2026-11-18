char __cdecl bppm_symbol(float *x)
{
  if ( *x > 0.667 )
    return 46;
  if ( x[1] > 0.667 )
    return 40;
  if ( x[2] > 0.667 )
    return 41;
  if ( (float)(x[1] + x[2]) <= *x )
  {
    if ( *x <= (float)(x[1] + x[2]) )
      return 58;
    else
      return 44;
  }
  else if ( (float)(x[1] / (float)(x[1] + x[2])) <= 0.667 )
  {
    if ( (float)(x[2] / (float)(x[1] + x[2])) <= 0.667 )
      return 124;
    else
      return 125;
  }
  else
  {
    return 123;
  }
}