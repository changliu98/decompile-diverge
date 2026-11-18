void mat3mulv(float *dest,float *mat,float *v)

{
  int i;
  float x;
  int k;
  float *v_local;
  float *mat_local;
  float *dest_local;
  
  for (k = 0; k < 3; k = k + 1) {
    x = 0.0;
    for (i = 0; i < 3; i = i + 1) {
      x = mat[k * 3 + i] * v[i] + x;
    }
    dest[k] = x;
  }
  return;
}