void getTransf(double *u10,double *N,double *D)

{
  double *D_local;
  double *N_local;
  double *u10_local;
  
  *D = u10[2];
  D[1] = u10[3];
  D[2] = 0.0;
  D[3] = 0.0;
  D[4] = u10[4];
  D[5] = 0.0;
  D[6] = *u10;
  D[7] = u10[1];
  D[8] = DAT_00102008;
  *N = DAT_00102008 / u10[7];
  N[1] = (-u10[8] / u10[7]) / u10[9];
  N[2] = 0.0;
  N[3] = 0.0;
  N[4] = DAT_00102008 / u10[9];
  N[5] = 0.0;
  N[6] = -u10[5] / u10[7];
  N[7] = ((u10[8] * u10[5] + -(u10[7] * u10[6])) / u10[7]) / u10[9];
  N[8] = DAT_00102008;
  return;
}