void OsdGetBSplineWeights(float x, float *w, float *dw, float *d2w)
{
  float x2 = x*x;
  float x3 = x2*x;
  w[0] = -1./6.*(x-x2+x3);
  w[1] = 1./2.*(x2-2.*x3);
  w[2] = -1./2.*(x+x2-x3);
  w[3] = 1./6.*x3;
  if (dw) {
    dw[0] = -1./2.*(x2-1./2.*x);
    dw[1] = -1./2.*(x2+1./2.*x);
    dw[2] = 1./2.*(x2-1./2.*x);
    dw[3] = 1./2.*x2;
  }
  if (d2w) {
    d2w[0] = -1./2.;
    d2w[1] = 3./2.*x;
    d2w[2] = -3./2.*x;
    d2w[3] = 1./2.*x;
  }
}