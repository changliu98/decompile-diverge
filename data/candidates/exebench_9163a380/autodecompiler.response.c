void
rmHSVtoRGB(float hue, float sat, float val, float *r, float *g, float *b)
{
   float p, q, t, f;
   int i;

   float _r = 0, _g = 0, _b = 0;

   p = 0;
   q = 0;
   t = 0;
   f = 0;
   i = 0;
   p = hue;
   if (val == 0)
     {
        _r = 0;
        _g = 0;
        _b = 0;
     }
   else
     {
        if (sat == 0)
          {
             _r = val;
             _g = val;
             _b = val;
          }
        else
          {
             float fl;

             p *= 6;
             if (p >= 6)
                p = 0;
             i = (int) p;
             f = p - i;
             p = val * (1 - sat);
             q = val * (1 - (sat * f));
             t = val * (1 - (sat * (1 - f)));
             if (i == 0)
               {
                  _r = val;
                  _g = t;
                  _b = p;
               }
             else if (i == 1)
               {
                  _r = q;
                  _g = val;
                  _b = p;
               }
             else if (i == 2)
               {
                  _r = p;
                  _g = val;
                  _b = t;
               }
             else if (i == 3)
               {
                  _r = p;
                  _g = q;
                  _b = val;
               }
             else if (i == 4)
               {
                  _r = t;
                  _g = p;
                  _b = val;
               }
             else if (i == 5)
               {
                  _r = val;
                  _g = p;
                  _b = q;
               }
          }
     }
   *r = _r;
   *g = _g;
   *b = _b;
}