static void func0(float *f, float a, float b, float c, float d)
{
   float s = 1.0f/29.0f;
   float aa = *f;
   if (aa == a) return;
   if (aa > a) {
      float t = d*pow((aa/a), 1.0f/3.0f);
      if (t > 0) {
         t = -log(t)/s;
         if (t < 0) t = -t;
      } else {
         t = -t;
      }
      aa = aa*pow((1.0f+t), s);
   } else {
      float t = pow((aa/a), 1.0f/3.0f);
      aa = aa + d*t*(t-1.0f);
      if (aa > a) aa = a;
      aa = aa*pow((1.0f+t), s);
   }
   *f = aa;
}