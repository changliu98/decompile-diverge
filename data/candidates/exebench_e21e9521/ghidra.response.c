float avg12(float *BufX,float *BufY,size_t Cnt)

{
  float local_34;
  size_t n;
  float Avg;
  size_t Cnt_local;
  float *BufY_local;
  float *BufX_local;
  
  Avg = 0.0;
  for (n = 0; n < Cnt; n = n + 1) {
    Avg = BufY[n] * BufX[n] * BufX[n] + Avg;
  }
  local_34 = (float)Cnt;
  return Avg / local_34;
}