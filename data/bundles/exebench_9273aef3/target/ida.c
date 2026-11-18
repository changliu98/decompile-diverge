void __cdecl mult_xps_vec(float *v, const float *M, const float *u)
{
  *v = (float)(M[3] * u[3]) + (float)((float)(M[2] * u[2]) + (float)((float)(*M * *u) + (float)(M[1] * u[1])));
  v[1] = (float)(M[7] * u[3]) + (float)((float)(M[6] * u[2]) + (float)((float)(M[4] * *u) + (float)(M[5] * u[1])));
  v[2] = (float)(M[11] * u[3]) + (float)((float)(M[10] * u[2]) + (float)((float)(M[8] * *u) + (float)(M[9] * u[1])));
  v[3] = (float)(M[15] * u[3]) + (float)((float)(M[14] * u[2]) + (float)((float)(M[12] * *u) + (float)(M[13] * u[1])));
}