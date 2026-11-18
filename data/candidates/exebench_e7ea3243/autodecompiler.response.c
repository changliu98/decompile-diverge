static void rifft2pt(float *e, float k)
{
   float k2 = 2*k;
   float f0r,f0i,f1r,f1i,t0r,t0i;
   t0r = e[0];
   t0i = e[1];
   f1r = 2*e[2];
   f1i = 2*e[3];
   f0r = t0r + t0i;
   f0i = t0r - t0i;
   t0r = f0r + f1r;
   t0i = f0i - f1i;
   f1r = f0r - f1r;
   f1i = f0i + f1i;
   e[0] = k*t0r;
   e[1] = k*t0i;
   e[2] = k*f1r;
   e[3] = k*f1i;
}