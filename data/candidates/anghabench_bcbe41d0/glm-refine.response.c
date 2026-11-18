float __cdecl constrain(float min, float max, float a)
{
  if (a < min)
    return min;
  if (a > max)
    return max;
  return a;
}