void geom_matmat2f(float *A, float *B, float *C)
 {

 const int bs = 4;
 const int lda = bs;
 const int ldc = bs;

 C[0+ldc*0] = A[0+lda*0] * B[0+lda*0] + A[2+lda*0] * B[1+lda*0];
 C[1+ldc*0] = A[1+lda*0] * B[0+lda*0] + A[3+lda*0] * B[1+lda*0];

 C[0+ldc*1] = A[0+lda*0] * B[0+lda*1] + A[2+lda*0] * B[1+lda*1];
 C[1+ldc*1] = A[1+lda*0] * B[0+lda*1] + A[3+lda*0] * B[1+lda*1];

 }