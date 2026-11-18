void vscal(float *a,float ca,float *v)

{
  float *v_local;
  float ca_local;
  float *a_local;
  
  *v = *a * ca;
  v[1] = a[1] * ca;
  v[2] = a[2] * ca;
  return;
}