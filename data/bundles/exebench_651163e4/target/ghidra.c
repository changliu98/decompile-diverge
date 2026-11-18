int matV3toV4(double *v3,double *v4)

{
  double *v4_local;
  double *v3_local;
  
  *v4 = *v3;
  v4[1] = v3[1];
  v4[2] = v3[2];
  v4[3] = DAT_00102008;
  return 0;
}