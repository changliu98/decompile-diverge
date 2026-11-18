double icvDotProduct_32f(float *src1,float *src2,int len)

{
  int i;
  double s;
  int len_local;
  float *src2_local;
  float *src1_local;
  
  s = 0.0;
  for (i = 0; i < len; i = i + 1) {
    s = (double)(src1[i] * src2[i]) + s;
  }
  return s;
}