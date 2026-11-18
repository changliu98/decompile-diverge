static inline float constrain(float min, float max, float v)
{
  if (v < min)
    return min;
  if (v > max)
    return max;
  return v;
}