float func0(float a, float b, float c)
{
  if (a + b < c || a + c < b || b + c < a)
    return -1.0;
  return roundf(100 * sqrtf((a + b + c) / 2 * ((a + b + c) / 2 - a) * ((a + b + c) / 2 - b) * ((a + b + c) / 2 - c))) / 100;
}