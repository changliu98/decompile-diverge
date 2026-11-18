float qdot(float *vec_a,float *vec_b)

{
  float *temp_b;
  float *temp_a;
  
  return vec_a[3] * vec_b[3] + vec_a[2] * vec_b[2] + *vec_a * *vec_b + vec_a[1] * vec_b[1];
}