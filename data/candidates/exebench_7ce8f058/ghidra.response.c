void SnapVector(float *v)

{
  float *v_local;
  
  *v = (float)(int)*v;
  v[1] = (float)(int)v[1];
  v[2] = (float)(int)v[2];
  return;
}