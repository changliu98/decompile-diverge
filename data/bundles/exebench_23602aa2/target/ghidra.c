void lib3ds_quat_scalar(float *c,float k)

{
  int i;
  float k_local;
  float *c_local;
  
  for (i = 0; i < 4; i = i + 1) {
    c[i] = k * c[i];
  }
  return;
}