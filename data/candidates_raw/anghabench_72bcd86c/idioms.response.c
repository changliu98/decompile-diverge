static float fmodf(float a, float b)
{
  if (b - a > 180.0f)
    b -= 360.0f;
  if (b - a < -180.0f)
    b += 360.0f;
  return a + (b - a) * (float)(b - a > 180.0f);
}