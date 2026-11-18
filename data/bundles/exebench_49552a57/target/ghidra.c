int matV4toV3(double *v4,double *v3)

{
  double *v3_local;
  double *v4_local;
  
  *v3 = *v4;
  v3[1] = v4[1];
  v3[2] = v4[2];
  return 0;
}