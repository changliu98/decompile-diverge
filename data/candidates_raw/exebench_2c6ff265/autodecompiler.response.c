void transform44d3d(double *m1, double *m2, double *m3)
{
  register double m2r0 = m2[0];
  register double m2r1 = m2[1];
  register double m2r2 = m2[2];
  register double m1r0 = m1[0];
  register double m1r1 = m1[1];
  register double m1r2 = m1[2];
  register double m1r3 = m1[3];
  register double m1r4 = m1[4];
  register double m1r5 = m1[5];
  register double m1r6 = m1[6];
  register double m1r7 = m1[7];
  register double m1r8 = m1[8];
  m3[0] = (double) (m1r0 * m2r0 + m1r1 * m2r1 + m1r2 * m2r2);
  m3[1] = (double) (m1r3 * m2r0 + m1r4 * m2r1 + m1r5 * m2r2);
  m3[2] = (double) (m1r6 * m2r0 + m1r7 * m2r1 + m1r8 * m2r2);
}