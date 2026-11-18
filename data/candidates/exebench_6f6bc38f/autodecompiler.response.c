void geom_matmat2d(double *A, double *B, double *C)
 {

 const int bs = 4;

 C[0+bs*0] = A[0+bs*0]*B[0+bs*0] + A[2+bs*0]*B[1+bs*0];
 C[1+bs*0] = A[1+bs*0]*B[0+bs*0] + A[3+bs*0]*B[1+bs*0];

 C[0+bs*1] = A[0+bs*0]*B[0+bs*1] + A[2+bs*0]*B[1+bs*1];
 C[1+bs*1] = A[1+bs*0]*B[0+bs*1] + A[3+bs*0]*B[1+bs*1];

 }