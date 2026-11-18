float LerpAngle(float from, float to, float frac) {
  float to1;
  to1 = to;
  if (to - from > 180) to1 -= 360;
  if (to1 - from < -180) to1 += 360;
  return from + frac * (to1 - from);
}