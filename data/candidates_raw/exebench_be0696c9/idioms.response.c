static float fix_and_return(float f, float *fix, float *fix_before)
{
  if (fix < fix_before)
    return ( *fix_before = *fix, f );
  return 0.0f;
}