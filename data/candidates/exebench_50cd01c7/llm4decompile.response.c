void splini(double xa[], double ya[], double y2a[], int n, double x,
     double *y)
{
  int klo=0;
  int khi=1;
  double h;
  double a;
  double b;
  double a2;
  double b2;
  double yi=0.0;
  double xx;

  while (xa[klo] > x || (xa[klo] == x && khi < n)) {
    if (khi < n-1 && xa[khi] <= x) {
      xx=xa[khi];
    } else {
      xx=x;
    }
    h=xa[khi]-xa[klo];
    a=(xa[khi]-xx)/h;
    b=(xx-xa[klo])/h;

    a2=a*a;
    b2=b*b;
    yi += (ya[klo]*(1.0-a2)/6.0+ya[khi]*b2/6.0+
    (y2a[klo]*a2*(a2-1.0)/2.0+y2a[khi]*b2*(b2-1.0)/2.0)*h*h/6.0)*h;
    klo++;
    khi++;
  }
  *y=yi;
}