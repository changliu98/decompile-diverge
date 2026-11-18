static unsigned int hsv2grb(unsigned int h, unsigned int s, unsigned int v)
{
  unsigned int r; unsigned int g; unsigned int b;
  unsigned int f; unsigned int p; unsigned int q; unsigned int t;
  unsigned int i;
  h = h % 360;
  s = s % 100;
  v = v % 100;
  h = h / (360 / 6);
  if (h < 1)
  {
    r = v;
    g = (v * (s ^ 0xff)) >> 8;
    b = (v * (s ^ 0xff)) >> 8;
  }
  else if (h < 2)
  {
    r = (v * (s ^ 0xff)) >> 8;
    g = v;
    b = (v * (s ^ 0xff)) >> 8;
  }
  else if (h < 3)
  {
    r = (v * (s ^ 0xff)) >> 8;
    g = v;
    b = (v * (s ^ 0xff)) >> 8;
  }
  else if (h < 4)
  {
    r = (v * (s ^ 0xff)) >> 8;
    g = (v * (s ^ 0xff)) >> 8;
    b = v;
  }
  else if (h < 5)
  {
    r = (v * (s ^ 0xff)) >> 8;
    g = (v * (s ^ 0xff)) >> 8;
    b = v;
  }
  else
  {
    r = v;
    g = (v * (s ^ 0xff)) >> 8;
    b = (v * (s ^ 0xff)) >> 8;
  }
  return (r << 16) | (g << 8) | b;
}