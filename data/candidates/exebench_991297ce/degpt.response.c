void mlVectorDotProductTo(float *vec_a,float *vec_b,float *output)
{
  *output = vec_a[2] * vec_b[2] + *vec_a * *vec_b + vec_a[1] * vec_b[1];
}