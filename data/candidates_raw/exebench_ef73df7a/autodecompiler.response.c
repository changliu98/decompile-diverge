void kernel_dgemm_nt_3x3_lib4(int kmax, double *A, double *B, double *C, double *D, double *sum)
 {

 double
  a_0, a_1, a_2,
  b_0, b_1, b_2,
  c_00=0, c_01=0, c_02=0,
  c_10=0, c_11=0, c_12=0;

 int k;

 for(k=0; k<kmax-1; k+=2)
  {

  a_0 = A[0+0*ldm];
  a_1 = A[1+0*ldm];
  a_2 = A[2+0*ldm];

  b_0 = B[0+0*ldm];
  b_1 = B[1+0*ldm];
  b_2 = B[2+0*ldm];

  c_00 += a_0 * b_0;
  c_10 += a_1 * b_0;
# 1080 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/giaf/hpmpc/refs/heads/master/kernel/avx/kernel_dgemm_avx_lib4.c"
  c_01 += a_0 * b_1;
  c_11 += a_1 * b_1;




  c_02 += a_0 * b_2;
  c_12 += a_1 * b_2;


  a_0 = A[0+1*ldm];
  a_1 = A[1+1*ldm];
  a_2 = A[2+1*ldm];

  b_0 = B[0+1*ldm];
  b_1 = B[1+1*ldm];
  b_2 = B[2+1*ldm];

  c_00 += a_0 * b_0;
  c_10 += a_1 * b_0;





  c_01 += a_0 * b_1;
  c_11 += a_1 * b_1;



  c_02 += a_0 * b_2;
  c_12 += a_1 * b_2;


  A += 2*ldm;
  B += 2*ldm;

  }

 a_0 = A[0+0*ldm];
 a_1 = A[1+0*ldm];
 a_2 = A[2+0*ldm];

 b_0 = B[0+0*ldm];
 b_1 = B[1+0*ldm];
 b_2 = B[2+0*ldm];

 c_00 += a_0 * b_0;
 c_10 += a_1 * b_0;
# 1140 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/giaf/hpmpc/refs/heads/master/kernel/avx/kernel_dgemm_avx_lib4.c"
 c_01 += a_0 * b_1;
 c_11 += a_1 * b_1;




 c_02 += a_0 * b_2;
 c_12 += a_1 * b_2;


 sum[0] = c_00;
 sum[1] = c_10;
 sum[2] = c_01;
 sum[3] = c_11;
 sum[4] = c_02;
 sum[5] = c_12;

 }