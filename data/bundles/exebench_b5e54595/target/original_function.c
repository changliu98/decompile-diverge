int
zuchk_(double* yr, double* yi, int* nz, double* ascle, double* tol)
{
 double wi, ss, st, wr;
# 6754 "zbsubs.c"
 *nz = 0;
 wr = ((*yr) >= 0 ? (*yr) : -(*yr));
 wi = ((*yi) >= 0 ? (*yi) : -(*yi));
 st = ((wr) <= (wi) ? (wr) : (wi));
 if (st > *ascle)
 {
  return 0;
 }
 ss = ((wr) >= (wi) ? (wr) : (wi));
 st /= *tol;
 if (ss < st)
 {
  *nz = 1;
 }
 return 0;
}