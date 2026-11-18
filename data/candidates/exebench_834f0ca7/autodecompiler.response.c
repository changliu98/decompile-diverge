void
FindDivDiff5Coeff1(double x0, double x1, double x2, double *f)
{
 double m0, m1, m2;

 m0 = 1.0 / (x1 - x0);
 m1 = 1.0 / (x2 - x0);
 m2 = 1.0 / (x2 - x1);

 f[1] = m0 * m0 * m1 * m1;
 f[0] = 2.0 * (m1 + m0) * f[1];

 f[3] = m2 * m2 * m0 * m0;
 f[2] = 2.0 * (m2 - m0) * f[3];

 f[5] = m2 * m2 * m1 * m1;
 f[4] = -2.0 * (m2 + m1) * f[5];
}