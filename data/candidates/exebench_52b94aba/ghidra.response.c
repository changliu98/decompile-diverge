float qdot(float *a,float *b)

{
  float *b_local;
  float *a_local;
  
  return a[3] * b[3] + a[2] * b[2] + *a * *b + a[1] * b[1];
}