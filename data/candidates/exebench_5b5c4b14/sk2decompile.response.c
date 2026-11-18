int jrand_(int *n, int *i, int *j, int *k) {
  static int im = 30269, ia = 30307, ic = 30323;
  static double d, r;
  *i = 171 * *i % im;
  *j = 172 * *j % ia;
  *k = 170 * *k % ic;
  d = (double)*i / im + (double)*j / ia + (double)*k / ic;
  r = d - (int)d;
  return (int)(1. + *n * r);
}