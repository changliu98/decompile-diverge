void __cdecl mult_mat_vec(float *v, const float *M, const float *u)
{
  *v = (float)(M[12] * u[3]) + (float)((float)(M[8] * u[2]) + (float)((float)(*M * *u) + (float)(M[4] * u[1])));
  v[1] = (float)(M[13] * u[3]) + (float)((float)(M[9] * u[2]) + (float)((float)(M[1] * *u) + (float)(M[5] * u[1])));
  v[2] = (float)(M[14] * u[3]) + (float)((float)(M[10] * u[2]) + (float)((float)(M[2] * *u) + (float)(M[6] * u[1])));
  v[3] = (float)(M[15] * u[3]) + (float)((float)(M[11] * u[2]) + (float)((float)(M[3] * *u) + (float)(M[7] * u[1])));
}