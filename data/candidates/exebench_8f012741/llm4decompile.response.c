void lin_solve_2(double x[2], double A[2][2], double y[2])
{
 double idet = 1.0 / (A[0][0] * A[1][1] - A[0][1] * A[1][0]);
 x[0] = (A[1][1] * y[0] - A[0][1] * y[1]) * idet;
 x[1] = (A[0][0] * y[1] - A[1][0] * y[0]) * idet;
}