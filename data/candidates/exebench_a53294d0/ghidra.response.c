int matCopyVdf(double *v1,float *v2)

{
  float *v2_local;
  double *v1_local;
  
  *v2 = (float)*v1;
  v2[1] = (float)v1[1];
  v2[2] = (float)v1[2];
  return 0;
}