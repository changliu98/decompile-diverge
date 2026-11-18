double root(double *f, int n) {
 double x = 0, y, g;
 int i, j;

 for (i = 1; ; ++i) {
  if (i >= n)
   break;

  double p = 1;

  for (j = 0; j < i; ++j)
   p *= x;

  y += f[i] * p;
 }

 while (1) {
  if (fabs(y) < 0.000001)
   return x;

  g = 0;

  for (i = 1; ; ++i) {
   if (i >= n)
    break;

   double p = 1;

   for (j = 1; j < i; ++j)
    p *= x;

   g += i * f[i] * p;
  }

  x -= y / g;
  y = f[0];

  for (i = 1; ; ++i) {
   if (i >= n)
    break;

   double p = 1;

   for (j = 0; j < i; ++j)
    p *= x;

   y += f[i] * p;
  }
 }
}