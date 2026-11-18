float __cdecl clamp(float x, float min, float max)
{
  if ( min > x )
    return min;
  if ( x <= max )
    return x;
  return max;
}