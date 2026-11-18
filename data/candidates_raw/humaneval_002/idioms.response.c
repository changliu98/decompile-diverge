static inline float fmodf(float x, float y)
{
  return x - (float)(int)x;
}