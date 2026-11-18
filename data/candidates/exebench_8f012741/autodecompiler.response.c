void lin_solve_2(double *C, double *A, double *B)
 {

 const int bs = 4;

 double
  c_00,
  c_10, c_11;


 c_00 = 1.0 / (A[0+bs*0] * A[1+bs*1] + ((A[1+bs*0]) >= 0 ? (A[1+bs*0]) : -(A[1+bs*0])));

 C[0+bs*0] = c_00 * (A[1+bs*1] * B[0+bs*0] + ((A[1+bs*0]) >= 0 ? (A[1+bs*0]) : -(A[1+bs*0])) * B[1+bs*0]);
 C[1+bs*0] = c_00 * (A[0+bs*0] * B[1+bs*0] + ((A[1+bs*1]) >= 0 ? (A[1+bs*1]) : -(A[1+bs*1])) * B[0+bs*0]);

 }