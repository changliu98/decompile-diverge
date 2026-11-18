void __cdecl add_ang_mom(double *L, float *c, float *pos)
{
  *L = (float)((float)(pos[1] - c[1]) * (float)(pos[5] - c[5])) + *L;
  *L = *L - (float)((float)(pos[2] - c[2]) * (float)(pos[4] - c[4]));
  L[1] = (float)((float)(pos[2] - c[2]) * (float)(pos[3] - c[3])) + L[1];
  L[1] = L[1] - (float)((float)(*pos - *c) * (float)(pos[5] - c[5]));
  L[2] = (float)((float)(*pos - *c) * (float)(pos[4] - c[4])) + L[2];
  L[2] = L[2] - (float)((float)(pos[1] - c[1]) * (float)(pos[3] - c[3]));
}