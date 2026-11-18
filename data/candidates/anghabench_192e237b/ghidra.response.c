double estLog(double N)

{
  double x;
  double logN;
  double N_local;
  
  logN = DAT_00102010;
  for (x = DAT_00102008; x < N; x = DAT_00102008 * x) {
    logN = DAT_00102010 + logN;
  }
  return logN;
}