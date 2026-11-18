void add_ang_mom(double *L,float *c,float *pos)

{
  float *pos_local;
  float *c_local;
  double *L_local;
  
  *L = (double)((pos[1] - c[1]) * (pos[5] - c[5])) + *L;
  *L = *L - (double)((pos[2] - c[2]) * (pos[4] - c[4]));
  L[1] = (double)((pos[2] - c[2]) * (pos[3] - c[3])) + L[1];
  L[1] = L[1] - (double)((*pos - *c) * (pos[5] - c[5]));
  L[2] = (double)((*pos - *c) * (pos[4] - c[4])) + L[2];
  L[2] = L[2] - (double)((pos[1] - c[1]) * (pos[3] - c[3]));
  return;
}