float pluck(float sig,float *q)

{
  int iVar1;
  int len;
  int ip;
  float temp;
  float *q_local;
  float sig_local;
  float local_c;
  
  *q = DAT_00102004 + *q;
  if (q[1] <= *q) {
    *q = DAT_00102008;
    local_c = q[4];
    q[4] = q[3] * q[(int)((double)q[1] - DAT_00102010)] + q[2] * q[4] + sig;
  }
  else {
    iVar1 = (int)*q;
    local_c = q[iVar1];
    q[iVar1] = q[3] * q[iVar1 + -1] + q[2] * q[iVar1] + sig;
  }
  return local_c;
}