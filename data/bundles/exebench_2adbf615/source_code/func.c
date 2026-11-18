
void daxpy (unsigned int n, const double da, const double *dx, double *dy)
{
 if(da == 0.0) {
  return;
 }
 if(da == 1.0) {
  do {
   --n;
   dy[n] += dx[n];
  } while(n);
 } else {
  do {
   --n;
   dy[n] += da*dx[n];
  } while(n);
 }
}
