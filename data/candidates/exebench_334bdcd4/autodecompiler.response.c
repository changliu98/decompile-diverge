void ZVdotC31(int kmax, double *A, double *B, double *C, double *D, double *E, int alg)
 {

 const int lda = 4;
 const int ldc = 4;

 int k;

 double
  a_0, a_1, a_2,
  b_0, b_1,
  c_00=0, c_01=0,
  c_10=0, c_11=0,
  c_20=0, c_21=0;

 for(k=0; k<kmax-1; k+=2)
  {

  a_0 = A[0+lda*0];
  a_1 = A[1+lda*0];
  a_2 = A[2+lda*0];

  b_0 = B[0+lda*0];
  b_1 = B[1+lda*0];

  c_00 += a_0 * b_0;
  c_10 += a_1 * b_0;
  c_20 += a_2 * b_0;

  c_01 += a_0 * b_1;
  c_11 += a_1 * b_1;
  c_21 += a_2 * b_1;


  a_0 = A[0+lda*1];
  a_1 = A[1+lda*1];
  a_2 = A[2+lda*1];

  b_0 = B[0+lda*1];
  b_1 = B[1+lda*1];

  c_00 += a_0 * b_0;
  c_10 += a_1 * b_0;
  c_20 += a_2 * b_0;

  c_01 += a_0 * b_1;
  c_11 += a_1 * b_1;
  c_21 += a_2 * b_1;


  A += 8;
  B += 8;

  }
 for(; k<kmax; k++)
  {

  a_0 = A[0+lda*0];
  a_1 = A[1+lda*0];
  a_2 = A[2+lda*0];

  b_0 = B[0+lda*0];
  b_1 = B[1+lda*0];

  c_00 += a_0 * b_0;
  c_10 += a_1 * b_0;
  c_20 += a_2 * b_0;

  c_01 += a_0 * b_1;
  c_11 += a_1 * b_1;
  c_21 += a_2 * b_1;


  A += 4;
  B += 4;

  }

 double
  d_00, d_01,
  d_10, d_11,
  d_20, d_21;

 if(alg==0)
  {
  E[0+ldc*0] = c_00;
  E[1+ldc*0] = c_10;
  E[2+ldc*0] = c_20;

  E[0+ldc*1] = c_01;
  E[1+ldc*1] = c_11;
  E[2+ldc*1] = c_21;
  }
 else
  {
  d_00 = D[0+ldc*0];
  d_10 = D[1+ldc*0];
  d_20 = D[2+ldc*0];

  d_01 = D[0+ldc*1];
  d_11 = D[1+ldc*1];
  d_21 = D[2+ldc*1];

  if(alg==1)
   {
   d_00 += c_00;
   d_10 += c_10;
   d_20 += c_20;

   d_01 += c_01;
   d_11 += c_11;
   d_21 += c_21;
   }
  else
   {
   d_00 -= c_00;
   d_10 -= c_10;
   d_20 -= c_20;

   d_01 -= c_01;
   d_11 -= c_11;
   d_21 -= c_21;
   }

  E[0+ldc*0] = c_00;
  E[1+ldc*0] = c_10;
  E[2+ldc*0] = c_20;

  E[0+ldc*1] = c_01;
  E[1+ldc*1] = c_11;
  E[2+ldc*1] = c_21;
  }

 }