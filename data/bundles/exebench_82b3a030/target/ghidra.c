int intwt(double N,double *W)

{
  int i;
  double *W_local;
  double N_local;
  
  if (N < DAT_00102008) {
    i = 1;
    *W = N;
  }
  if (DAT_00102008 <= N) {
    i = (int)N;
    *W = DAT_00102008;
  }
  return i;
}