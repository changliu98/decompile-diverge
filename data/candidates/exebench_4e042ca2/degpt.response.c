void mat4f_LoadScale(float *s,float *m)

{
  float *m_local;
  float *s_local;
  
  *m = *s;
  m[1] = 0.0;
  m[2] = 0.0;
  m[3] = 0.0;
  m[4] = 0.0;
  m[5] = s[1];
  m[6] = 0.0;
  m[7] = 0.0;
  m[8] = 0.0;
  m[9] = 0.0;
  m[10] = s[2];
  m[0xb] = 0.0;
  m[0xc] = 0.0;
  m[0xd] = 0.0;
  m[0xe] = 0.0;
  m[0xf] = DAT_00102004;
  return;
}