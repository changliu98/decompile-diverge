float getUniform(int a,int c,int m,float *x)

{
  float fVar1;
  int num_mod;
  float num;
  float *x_local;
  int m_local;
  int c_local;
  int a_local;
  
  fVar1 = (float)a * *x + (float)c;
  *x = (fVar1 - (float)((int)(fVar1 / (float)m) * m)) / (float)m;
  return *x;
}