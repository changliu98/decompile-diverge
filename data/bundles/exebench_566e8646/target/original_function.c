static void lin_solve_3(double x[3], const double A[9], const double y[3])
{
  const double a = A[4]*A[8]-A[5]*A[7],
               b = A[5]*A[6]-A[3]*A[8],
               c = A[3]*A[7]-A[4]*A[6],
            idet = 1/(A[0]*a+A[1]*b+A[2]*c);
  const double
    inv0 = a,
    inv1 = A[2]*A[7]-A[1]*A[8],
    inv2 = A[1]*A[5]-A[2]*A[4],
    inv3 = b,
    inv4 = A[0]*A[8]-A[2]*A[6],
    inv5 = A[2]*A[3]-A[0]*A[5],
    inv6 = c,
    inv7 = A[1]*A[6]-A[0]*A[7],
    inv8 = A[0]*A[4]-A[1]*A[3];
  x[0] = idet*(inv0*y[0] + inv1*y[1] + inv2*y[2]);
  x[1] = idet*(inv3*y[0] + inv4*y[1] + inv5*y[2]);
  x[2] = idet*(inv6*y[0] + inv7*y[1] + inv8*y[2]);
}