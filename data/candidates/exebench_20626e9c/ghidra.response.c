void unscale(double *prob,uint times)

{
  uint i;
  uint times_local;
  double *prob_local;
  
  for (i = 0; i < times; i = i + 1) {
    *prob = DAT_00102010 * *prob;
  }
  return;
}