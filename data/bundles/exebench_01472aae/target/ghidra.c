void mlMatrixLoadPositionTransposedRotation(float *m,float *p,float *r)

{
  float *r_local;
  float *p_local;
  float *m_local;
  
  *m = *r;
  m[1] = r[4];
  m[2] = r[8];
  m[3] = 0.0;
  m[4] = r[1];
  m[5] = r[5];
  m[6] = r[9];
  m[7] = 0.0;
  m[8] = r[2];
  m[9] = r[6];
  m[10] = r[10];
  m[0xb] = 0.0;
  m[0xc] = *p;
  m[0xd] = p[1];
  m[0xe] = p[2];
  m[0xf] = DAT_00102004;
  return;
}