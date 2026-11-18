float FDot(float *vec1,float *vec2,int n)

{
  int x;
  float result;
  int n_local;
  float *vec2_local;
  float *vec1_local;
  
  result = 0.0;
  for (x = 0; x < n; x = x + 1) {
    result = vec1[x] * vec2[x] + result;
  }
  return result;
}