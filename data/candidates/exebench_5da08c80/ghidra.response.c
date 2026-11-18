_Bool mmeq(float *A,float *B,size_t rows,size_t cols)

{
  int i;
  size_t cols_local;
  size_t rows_local;
  float *B_local;
  float *A_local;
  
  i = 0;
  while( true ) {
    if (rows * cols <= (ulong)(long)i) {
      return true;
    }
    if ((A[i] != B[i]) || (NAN(A[i]) || NAN(B[i]))) break;
    i = i + 1;
  }
  return false;
}