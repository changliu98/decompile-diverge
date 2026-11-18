void load_xps(float *M,float *N)

{
  float *N_local;
  float *M_local;
  
  *M = *N;
  M[4] = N[1];
  M[8] = N[2];
  M[0xc] = N[3];
  M[1] = N[4];
  M[5] = N[5];
  M[9] = N[6];
  M[0xd] = N[7];
  M[2] = N[8];
  M[6] = N[9];
  M[10] = N[10];
  M[0xe] = N[0xb];
  M[3] = N[0xc];
  M[7] = N[0xd];
  M[0xb] = N[0xe];
  M[0xf] = N[0xf];
  return;
}