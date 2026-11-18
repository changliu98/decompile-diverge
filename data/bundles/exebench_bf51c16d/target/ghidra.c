int condF(int xn,float *xp,int yn,float *yp,int ltn,float *ltp,int eqn,float *eqp,int gtn,float *gtp
         ,int rn,float *rp)

{
  float local_44;
  float local_40;
  int k;
  float *ltp_local;
  int ltn_local;
  float *yp_local;
  int yn_local;
  float *xp_local;
  int xn_local;
  int local_c;
  
  if ((((xn == yn) && (xn == ltn)) && (xn == eqn)) && ((xn == gtn && (xn == rn)))) {
    for (k = 0; k < xn; k = k + 1) {
      if (yp[k] <= xp[k]) {
        if (xp[k] < yp[k] || xp[k] == yp[k]) {
          local_44 = eqp[k];
        }
        else {
          local_44 = gtp[k];
        }
        local_40 = local_44;
      }
      else {
        local_40 = ltp[k];
      }
      rp[k] = local_40;
    }
    local_c = 0;
  }
  else {
    local_c = 2000;
  }
  return local_c;
}