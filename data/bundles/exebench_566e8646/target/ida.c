void __cdecl lin_solve_3(double *x, const double *A, const double *y)
{
  double inv8; // [rsp+0h] [rbp-80h]
  double inv7; // [rsp+8h] [rbp-78h]
  double inv6; // [rsp+10h] [rbp-70h]
  double inv5; // [rsp+18h] [rbp-68h]
  double inv4; // [rsp+20h] [rbp-60h]
  double inv3; // [rsp+28h] [rbp-58h]
  double idet; // [rsp+48h] [rbp-38h]
  double a; // [rsp+60h] [rbp-20h]

  a = A[4] * A[8] - A[5] * A[7];
  idet = 1.0 / (A[2] * (A[3] * A[7] - A[4] * A[6]) + *A * a + A[1] * (A[5] * A[6] - A[3] * A[8]));
  inv3 = A[5] * A[6] - A[3] * A[8];
  inv4 = *A * A[8] - A[2] * A[6];
  inv5 = A[2] * A[3] - *A * A[5];
  inv6 = A[3] * A[7] - A[4] * A[6];
  inv7 = A[1] * A[6] - *A * A[7];
  inv8 = *A * A[4] - A[1] * A[3];
  *x = idet * ((A[1] * A[5] - A[2] * A[4]) * y[2] + a * *y + (A[2] * A[7] - A[1] * A[8]) * y[1]);
  x[1] = idet * (inv5 * y[2] + inv3 * *y + inv4 * y[1]);
  x[2] = idet * (inv8 * y[2] + inv6 * *y + inv7 * y[1]);
}