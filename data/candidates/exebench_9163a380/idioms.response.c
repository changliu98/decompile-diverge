void rmHSVtoRGB(float h, float s, float v, float *r, float *g, float *b)
{
  int i;
  float f;
  float m; float n; float k;
  float r1 = 0.0f; float g1 = 0.0f; float b1 = 0.0f;
  if (v == 0.0f)
  {
    r1 = 0.0f;
    g1 = 0.0f;
    b1 = 0.0f;
  }
  else if (s == 0.0f)
  {
    r1 = v;
    g1 = v;
    b1 = v;
  }
  else
  {
    i = (int) h * 6.0f;
    f = h * 6.0f - (float) i;
    if (i == 6.0f)
    {
      i = 0.0f;
    }
    m = v * (1.0f - s);
    n = v * (1.0f - s * f);
    k = v * (1.0f - s * (1.0f - f));
    switch (i)
    {
      case 0.0f:
        r1 = v;
        g1 = k;
        b1 = m;
        break;
      case 1.0f:
        r1 = n;
        g1 = v;
        b1 = m;
        break;
      case 2.0f:
        r1 = m;
        g1 = v;
        b1 = k;
        break;
      case 3.0f:
        r1 = m;
        g1 = n;
        b1 = v;
        break;
      case 4.0f:
        r1 = k;
        g1 = m;
        b1 = v;
        break;
      case 5.0f:
        r1 = v;
        g1 = m;
        b1 = n;
        break;
    }
  }
  *r = r1;
  *g = g1;
  *b = b1;
}