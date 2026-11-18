void daxpy(unsigned int n, double da, double *dx, double *dy)
{
  if(da != 0.0) {
    if(da == 1.0) {
      while(n > 0) {
        n--;
        dy[n] = dy[n] + dx[n];
      }
    } else {
      while(n > 0) {
        n--;
        dy[n] = dy[n] + da*dx[n];
      }
    }
  }
}