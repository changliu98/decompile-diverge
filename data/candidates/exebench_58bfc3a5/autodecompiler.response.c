void
FindDivDiff4Coeff(double z0, double z1, double z2, double z3, double z4,
 double *c)
{
 c[0] = 1.0 / ((z0-z1) * (z0-z2) * (z0-z3) * (z0-z4));
 c[1] = 1.0 / ((z1-z0) * (z1-z2) * (z1-z3) * (z1-z4));
 c[2] = 1.0 / ((z2-z0) * (z2-z1) * (z2-z3) * (z2-z4));
 c[3] = 1.0 / ((z3-z0) * (z3-z1) * (z3-z2) * (z3-z4));
 c[4] = 1.0 / ((z4-z0) * (z4-z1) * (z4-z2) * (z4-z3));
}