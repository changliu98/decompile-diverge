float hpluck(float xin,float *q)

{
  float fVar1;
  float fVar2;
  int ip;
  float temp;
  float *q_local;
  float xin_local;
  
  *q = DAT_00102004 + *q;
  if (q[1] < *q) {
    ip = 0x14;
    *q = DAT_00102008;
  }
  else {
    ip = (int)*q;
  }
  q[7] = (float)((DAT_00102010 - (double)q[8]) * (double)q[ip] + (double)(q[8] * q[7]));
  fVar2 = q[9] * (q[2] * q[ip] + q[3] * q[6]);
  q[6] = q[ip];
  q[ip] = -q[10] * q[5] + q[10] * fVar2 + q[4];
  fVar1 = q[ip];
  q[ip] = xin + fVar1;
  q[5] = xin + fVar1;
  q[4] = fVar2;
  return q[7];
}