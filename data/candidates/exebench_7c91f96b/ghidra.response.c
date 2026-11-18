void mm_us(float *m1,float *m2,float *mout)

{
  float su;
  int k;
  int j;
  int i;
  float *mout_local;
  float *m2_local;
  float *m1_local;
  
  for (i = 0; i < 4; i = i + 1) {
    for (j = 0; j < 4; j = j + 1) {
      su = 0.0;
      for (k = 0; k < 4; k = k + 1) {
        su = m1[i * 4 + k] * m2[k * 4 + j] + su;
      }
      mout[i * 4 + j] = su;
    }
  }
  return;
}