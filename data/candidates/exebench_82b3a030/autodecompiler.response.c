int
intwt(double x, double y, double *r)
{
 int n;

 if (x < 1) {
  n = 1;
  *r = x;
 }
 if (x >= 1) {
  n = (int)x;
  *r = 1;
 }

 return (n);
}