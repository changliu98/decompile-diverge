static inline float clamp(float min, float max, float v)
{
  if (v < min)
    return min;
  if (v > max)
    return max;
  return v;
}