void ZVdotU21( const int M, const double *A, const double *B, double *C, double *num )
{
 double real_0 = 0.0;
 double img_0 = 0.0;
 double real_1 = 0.0;
 double img_1 = 0.0;

 int i, j, k;

 for ( i = 0; i < M; i += 2 ) {
  double a_real = A[i];
  double a_img = A[i+1];

  double b_real = B[i];
  double b_img = B[i+1];

  double c_real = C[i];
  double c_img = C[i+1];

  real_0 += a_real * b_real + a_img * b_img;
  img_0 += a_real * b_img + a_img * b_real;

  real_1 += a_real * b_real + a_img * b_img;
  img_1 += a_real * b_img + a_img * b_real;
 }

 num[0] = real_0;
 num[1] = img_0;
 num[2] = real_1;
 num[3] = img_1;
}