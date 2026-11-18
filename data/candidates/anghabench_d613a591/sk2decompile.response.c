float RGB(float h, float r, float b) {
  if (h < 0)
    h += 360;
  else if (h > 360)
    h -= 360;
  if (h < 60)
    return r + (b - r) * h / 60;
  else if (h < 180)
    return b;
  else if (h < 240)
    return r + (b - r) * (240 - h) / 60;
  else
    return r;
}