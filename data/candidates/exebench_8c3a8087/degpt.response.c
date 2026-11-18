void vset(float *v,float x,float y,float z)

{
  float z_local;
  float y_local;
  float x_local;
  float *v_local;
  
  *v = x;
  v[1] = y;
  v[2] = z;
  return;
}