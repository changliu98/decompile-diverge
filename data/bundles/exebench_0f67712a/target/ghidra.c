int transF(int xr,int xc,float *xp,int tr,int tc,float *tp)

{
  int j;
  int i;
  float *tp_local;
  int tc_local;
  int tr_local;
  float *xp_local;
  int xc_local;
  int xr_local;
  int local_c;
  
  if ((xr == tc) && (xc == tr)) {
    for (i = 0; i < tr; i = i + 1) {
      for (j = 0; j < tc; j = j + 1) {
        tp[i * tc + j] = xp[j * xc + i];
      }
    }
    local_c = 0;
  }
  else {
    local_c = 2000;
  }
  return local_c;
}