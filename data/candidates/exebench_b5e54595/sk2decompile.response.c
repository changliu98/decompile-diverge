int zuchk_(doublereal *zr, doublereal *zi, integer *ns, doublereal *u,
           doublereal *tol) {
  doublereal zabs, zabs2, zabsmin;
  extern int dabs(doublereal);
  *ns = 0;
  zabs = ((*zr) >= 0 ? (*zr) : -(*zr));
  zabs2 = ((*zi) >= 0 ? (*zi) : -(*zi));
  zabsmin = ((zabs) <= (zabs2) ? (zabs) : (zabs2));
  if (zabsmin > *u) {
    return 0;
  }
  zabsmin /= *tol;
  if (zabsmin > ((zabs) >= (zabs2) ? (zabs) : (zabs2))) {
    *ns = 1;
  }
  return 0;
}