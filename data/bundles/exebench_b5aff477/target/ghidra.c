float dotprod(float *vector,float *vector2,int len)

{
  int i;
  float dot;
  int len_local;
  float *vector2_local;
  float *vector_local;
  
  dot = 0.0;
  for (i = 0; i < len; i = i + 1) {
    dot = vector[i] * vector2[i] + dot;
  }
  return dot;
}