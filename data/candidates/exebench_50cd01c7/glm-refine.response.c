void __cdecl splini(double *xa, double *ya, double *y2a, int n, double x, double *y)
{
  double yi = 0.0;
  int klo = 0;

  for (int khi = 1; khi < n && x > xa[klo]; ++khi)
  {
    double xx = x;
    
    // Clamp xx to xa[khi] if it's not the last interval and x exceeds xa[khi]
    if (khi < n - 1 && xa[khi] < x)
      xx = xa[khi];

    double h = xa[khi] - xa[klo];
    double a = (xa[khi] - xx) / h;
    double b = (xx - xa[klo]) / h;

    // Evaluate the cubic spline integral contribution for this interval
    double term1 = (1.0 - a * a) * ya[klo] / 2.0;
    double term2 = b * b * ya[khi] / 2.0;
    
    double a2 = a * a;
    double b2 = b * b;
    double term3 = ((-(a2 * a2 + 1.0) / 4.0 + a2 / 2.0) * y2a[klo] 
                  + (b2 * b2 / 4.0 - b2 / 2.0) * y2a[khi]) * h * h / 6.0;

    // Accumulate the integral
    yi += (term1 + term2 + term3) * h;
    
    ++klo;
  }
  
  *y = yi;
}