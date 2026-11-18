void __cdecl rmHSVtoRGB(float h, float s, float v, float *r, float *g, float *b)
{
  float rr = 0.0f;
  float gg = 0.0f;
  float bb = 0.0f;

  if (v != 0.0f)
  {
    if (s == 0.0f)
    {
      rr = v;
      gg = v;
      bb = v;
    }
    else
    {
      float ht = h * 6.0f;
      if (ht >= 6.0f)
        ht = 0.0f;

      int i = (int)ht;
      float f = ht - (float)i;

      float p = v * (1.0f - s);
      float q = v * (1.0f - s * f);
      float t = v * (1.0f - s * (1.0f - f));

      switch (i)
      {
        case 0:
          rr = v;
          gg = t;
          bb = p;
          break;
        case 1:
          rr = q;
          gg = v;
          bb = p;
          break;
        case 2:
          rr = p;
          gg = v;
          bb = t;
          break;
        case 3:
          rr = p;
          gg = q;
          bb = v;
          break;
        case 4:
          rr = t;
          gg = p;
          bb = v;
          break;
        case 5:
          rr = v;
          gg = p;
          bb = q;
          break;
      }
    }
  }

  *r = rr;
  *g = gg;
  *b = bb;
}