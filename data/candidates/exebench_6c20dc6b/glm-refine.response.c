void __cdecl getTransf(double *u10, double *N, double *D)
{
  // Matrix D (3x3 Row-Major)
  D[0] = u10[2];
  D[1] = u10[3];
  D[2] = 0.0;
  D[3] = 0.0;
  D[4] = u10[4];
  D[5] = 0.0;
  D[6] = u10[0];
  D[7] = u10[1];
  D[8] = 1.0;

  // Matrix N (3x3 Row-Major)
  double inv_w = 1.0 / u10[7];
  double inv_h = 1.0 / u10[9];
  
  N[0] = inv_w;
  N[1] = -u10[8] * inv_w * inv_h;
  N[2] = 0.0;
  N[3] = 0.0;
  N[4] = inv_h;
  N[5] = 0.0;
  N[6] = -u10[5] * inv_w;
  N[7] = (u10[8] * u10[5] - u10[7] * u10[6]) * inv_w * inv_h;
  N[8] = 1.0;
}