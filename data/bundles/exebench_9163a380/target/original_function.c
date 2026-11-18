void
rmHSVtoRGB (float h,
     float s,
     float v,
     float *r,
     float *g,
     float *b)
{
    int i;
    float f, p, q, t;
    float tr = 0.0, tg = 0.0, tb = 0.0;
    float ht;


    ht = h;

    if (v == 0.0)
    {
 tr=0.0;
 tg=0.0;
 tb=0.0;
    }
    else
    {
 if (s == 0.0)
 {
     tr = v;
     tg = v;
     tb = v;
 }
 else
 {
     ht = ht * 6.0;
     if (ht >= 6.0)
  ht = 0.0;

     i = ht;
     f = ht - i;
     p = v * (1.0 - s);
     q = v * (1.0 - s*f);
     t = v * (1.0 - (s * (1.0 - f)));

      if (i == 0)
     {
  tr = v;
  tg = t;
  tb = p;
     }
     else if (i == 1)
     {
  tr = q;
  tg = v;
  tb = p;
     }
     else if (i == 2)
     {
  tr = p;
  tg = v;
  tb = t;
     }
     else if (i == 3)
     {
  tr = p;
  tg = q;
  tb = v;
     }
     else if (i == 4)
     {
  tr = t;
  tg = p;
  tb = v;
     }
     else if (i == 5)
     {
  tr = v;
  tg = p;
  tb = q;
     }
 }
    }
    *r = tr;
    *g = tg;
    *b = tb;
}