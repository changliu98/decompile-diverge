int ctr_intersect(double c1, double c2, double p, double *r)
{
 int ok;
 if (((p > c1) ^ (p > c2)) || (p == c1) || (p == c2))
  ok = 0;
 else {
  *r = (p - c1) / (c2 - c1);
  ok = 1;
 }
 return ok;
}