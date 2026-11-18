float sp(float *a,float *b)

{
  float sp1;
  float *b_local;
  float *a_local;
  
  return a[2] * b[2] + *a * *b + a[1] * b[1];
}