float constrain(float min, float max, float a)
{
 if (a < min)
  return min;
 else if (a > max)
  return max;
 else
  return a;
}