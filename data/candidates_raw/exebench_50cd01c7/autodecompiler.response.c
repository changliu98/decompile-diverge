void spline(double *x,double *y,double *y2,int npoints, double xi, double *yi)
{
  int klo,khi,k;
  double h,b,a,result;

  result = 0.0;
  klo=0;
  khi=1;

  while (1) {
    if ((xi > x[klo]) && (khi < npoints)) {
      klo++;
      khi++;
    } else {
      break;
    }
  }

  while (1) {

    if (khi >= (npoints-1)) {
      h=x[khi]-x[klo];
      a=(x[khi]-xi)/h;
      b=(xi-x[klo])/h;
      result=a*y[klo]+b*y[khi]+((1-a2)*y2[klo]+(b2)*y2[khi])*(h*h)/6.0;
      break;
    } else {

      if (x[khi] > xi) {
 h=xi-x[klo];
      } else {
 h=x[khi]-x[klo];
      }

      a=(x[khi]-xi)/h;
      b=(xi-x[klo])/h;
      a2=a*a;
      b2=b*b;
      result=(1-a2)*y[klo]/2+(b2)*y[khi]/2+(1-a2)*(1-a2)/4*(y2[klo]-y2[khi])/6+(b2)*(b2)/4*(y2[khi]-y2[klo])/6;
      result=result*h+h;
      klo++;
      khi++;
    }
  }
  *yi = result;
}