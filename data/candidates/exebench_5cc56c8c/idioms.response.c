void computeRates(int n, double *x, double *gr, double *g, int *iflag)
{
  gr[1]=1.0*(-x[1]);
  gr[2]=1.0*x[0];
}