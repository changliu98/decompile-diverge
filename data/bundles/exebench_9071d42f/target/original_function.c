static inline void
cmul(double *aa, double *bb) {
   double rr= aa[0] * bb[0] - aa[1] * bb[1];
   double ii= aa[0] * bb[1] + aa[1] * bb[0];
   aa[0]= rr;
   aa[1]= ii;
}