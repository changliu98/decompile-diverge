int shape_tria3(double *L,double *N)

{
  double *N_local;
  double *L_local;
  
  *N = *L;
  N[1] = L[1];
  N[2] = (DAT_00102008 - *L) - L[1];
  return 0;
}