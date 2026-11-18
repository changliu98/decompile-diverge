void lib3ds_vector_max(float *c,float *a)

{
  int i;
  float *a_local;
  float *c_local;
  
  for (i = 0; i < 3; i = i + 1) {
    if (c[i] <= a[i] && a[i] != c[i]) {
      c[i] = a[i];
    }
  }
  return;
}