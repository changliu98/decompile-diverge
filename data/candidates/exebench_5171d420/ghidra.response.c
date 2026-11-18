int _inverse_rot(int *m,int *o)

{
  int *o_local;
  int *m_local;
  int local_c;
  
  if ((m[1] == 0) || (m[2] == 0)) {
    local_c = 1;
  }
  else {
    *o = 0;
    o[1] = (int)(0x100000 / (long)m[2]);
    o[2] = (int)(0x100000 / (long)m[1]);
    o[3] = 0;
    o[4] = -(m[5] * o[2]) / 0x400;
    o[5] = -(m[4] * o[1]) / 0x400;
    local_c = 0;
  }
  return local_c;
}