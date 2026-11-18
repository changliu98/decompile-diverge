void ecRotate(double c[3], double soe, double coe) {
   double e1 = c[2]*soe + c[1]*coe;
   c[2] = c[2]*coe - c[1]*soe;
   c[1] = e1;
}