float __cdecl constrain(float min, float max, float a)
{
  if ( min > a )
    return min;
  if ( a <= max )
    return a;
  return max;
}