static float _RGB(float h, float s, float v)
{
  if (h < 0)
    h += 360;
  else if (h > 360)
    h -= 360;
  if (h < 60)
    return s * (v - v * (h / 60)) + v;
  if (h < 180)
    return v;
  if (h < 240)
    return s * (v - v * ((240 - h) / 60)) + v;
  return v;
}