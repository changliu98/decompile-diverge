void scale_mat(int *m,int sx,int sy)

{
  int sy_local;
  int sx_local;
  int *m_local;
  
  if (sx != 0x400) {
    *m = (*m * sx) / 0x400;
    m[2] = (m[2] * sx) / 0x400;
    m[4] = (m[4] * sx) / 0x400;
  }
  if (sy != 0x400) {
    m[1] = (m[1] * sy) / 0x400;
    m[3] = (m[3] * sy) / 0x400;
    m[5] = (m[5] * sy) / 0x400;
  }
  return;
}