void math_matrix_copy(float *from,float *to)

{
  int i;
  float *to_local;
  float *from_local;
  
  for (i = 0; i < 0x10; i = i + 1) {
    to[i] = from[i];
  }
  return;
}