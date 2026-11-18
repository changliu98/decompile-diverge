
static inline void r3sums (double * w, double * u, double s, double * v, double t){
  w[0] = u[0]*s + v[0]*t;
  w[1] = u[1]*s + v[1]*t;
  w[2] = u[2]*s + v[2]*t;
  return;
}
