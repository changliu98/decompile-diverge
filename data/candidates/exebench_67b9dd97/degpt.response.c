float v_inner(float *v1,float *v2,int n)

{
  float innerprod;
  int i;
  int n_local;
  float *v2_local;
  float *v1_local;
  
  innerprod = 0.0;
  for (i = 0; i < n; i = i + 1) {
    innerprod = v1[i] * v2[i] + innerprod;
  }
  return innerprod;
}