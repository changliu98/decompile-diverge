int shape_tria6(double *L, double *N)
{
 double L1 = L[0];
 double L2 = L[1];
 double L3 = 1.0 - L1 - L2;

 N[0] = 2.0 * L1 * (2.0 * L1 + L2);
 N[1] = 4.0 * L1 * L2;
 N[2] = 2.0 * L2 * (2.0 * L2 + L1);
 N[3] = 4.0 * L2 * L3;
 N[4] = 2.0 * L3 * (2.0 * L3 + L2);
 N[5] = 4.0 * L1 * L3;

 return 0;
}