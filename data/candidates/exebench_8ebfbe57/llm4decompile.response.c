float spline_cubic_val(int n,float *t,float tval,float *y,float *ypp)
{
  int i;
  float yval;
  float dt;
  float h;

  i=n-2;
  while((i<n-1) && (tval>=t[i+1])) i++;

  dt=tval-t[i];
  h=t[i+1]-t[i];

  yval=y[i]+dt*(y[i+1]-y[i])/h
    +dt*dt*((ypp[i+1]-ypp[i])/(6.0*h)+ypp[i]/2.0)
    -dt*dt*dt*(ypp[i+1]/(6.0*h)+ypp[i]/(2.0*h));

  return yval;
}