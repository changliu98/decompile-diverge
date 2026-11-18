void mlVectorSub(float *a,float *b)

{
  uint i;
  float *b_local;
  float *a_local;
  
  for (i = 0; i < 3; i = i + 1) {
    a[i] = a[i] - b[i];
  }
  return;
}