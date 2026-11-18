void corner_dtrmm_l_u_nt_4x1_lib4(double *A, double *B, double *C, double kaa, double kbb)
 {

 const int bs = 4;

 C[0+bs*0] *= kbb;
 C[0+bs*0] += kaa*( A[0+bs*0]*B[0+bs*0] + A[1+bs*0]*B[1+bs*0] + A[2+bs*0]*B[2+bs*0] + A[3+bs*0]*B[3+bs*0] );

 C[1+bs*0] *= kbb;
 C[1+bs*0] += kaa*( A[0+bs*1]*B[0+bs*0] + A[1+bs*1]*B[1+bs*0] + A[2+bs*1]*B[2+bs*0] + A[3+bs*1]*B[3+bs*0] );

 C[2+bs*0] *= kbb;
 C[2+bs*0] += kaa*( A[0+bs*2]*B[0+bs*0] + A[1+bs*2]*B[1+bs*0] + A[2+bs*2]*B[2+bs*0] + A[3+bs*2]*B[3+bs*0] );

 C[3+bs*0] *= kbb;
 C[3+bs*0] += kaa*( A[0+bs*3]*B[0+bs*0] + A[1+bs*3]*B[1+bs*0] + A[2+bs*3]*B[2+bs*0] + A[3+bs*3]*B[3+bs*0] );

 }