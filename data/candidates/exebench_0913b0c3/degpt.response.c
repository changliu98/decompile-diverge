void mlSphereLoad(float *a,float x,float y,float z,float r)

{
  float r_local;
  float z_local;
  float y_local;
  float x_local;
  float *a_local;
  
  *a = x;
  a[1] = y;
  a[2] = z;
  a[3] = r;
  return;
}