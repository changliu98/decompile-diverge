int gcd_ptr(int *u, int *v)
{
 int *tmp;
 while (*u > 0) {
  if (*u < *v) {
   tmp = u;
   u = v;
   v = tmp;
  }
  *u = *u - *v;
 }
 return *v;
}