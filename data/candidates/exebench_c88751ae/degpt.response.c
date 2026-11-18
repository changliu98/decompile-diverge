int hmsra(int h,int m,float s,double *ra)

{
  double *ra_local;
  float s_local;
  int m_local;
  int h_local;
  undefined4 local_c;
  
  *ra = (double)h + (double)m / DAT_00102018 + (double)s / DAT_00102010;
  *ra = DAT_00102008 * *ra;
  if (0.0 < *ra || *ra == 0.0) {
    if (*ra <= DAT_00102020) {
      local_c = 0;
    }
    else {
      local_c = 1;
    }
  }
  else {
    local_c = 1;
  }
  return local_c;
}