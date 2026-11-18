static inline float modff(float x, float *px)
{
  int e;
  union {float f;int i;} u;
  float r;
  e = (int)(x) >> 23;
  e -= 127;
  if (e < 23)
  {
    if (e < 0)
    {
      u.i = (int)(x);
      u.i &= 0x80000000;
      *px = u.f;
      return x;
    }
    if ((int)(x) & (0x7fffff >> e))
    {
      u.i = (int)(x);
      u.i &= ~(0x7fffff >> e);
      *px = u.f;
      return x - u.f;
    }
    else
    {
      u.f = x;
      u.i = (int)(u.f);
      *px = u.f;
      return x - u.f;
    }
  }
  else
  {
    u.f = x;
    u.i = (int)(u.f);
    *px = u.f;
    if (e == 255 && (u.i & (1 << 23)))
      return x;
    else
    {
      u.i = (int)(x);
      u.i &= 0x80000000;
      return u.f;
    }
  }
}