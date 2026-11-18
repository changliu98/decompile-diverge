float reson(float x,float *a)

{
  float fVar1;
  float temp;
  float *a_local;
  float x_local;
  
  fVar1 = -a[2] * a[4] + *a * x + a[1] * a[3];
  a[4] = a[3];
  a[3] = fVar1;
  return fVar1;
}