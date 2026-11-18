void load_scl_mat(float *M,float x,float y,float z)

{
  float z_local;
  float y_local;
  float x_local;
  float *M_local;
  
  *M = x;
  M[4] = 0.0;
  M[8] = 0.0;
  M[0xc] = 0.0;
  M[1] = 0.0;
  M[5] = y;
  M[9] = 0.0;
  M[0xd] = 0.0;
  M[2] = 0.0;
  M[6] = 0.0;
  M[10] = z;
  M[0xe] = 0.0;
  M[3] = 0.0;
  M[7] = 0.0;
  M[0xb] = 0.0;
  M[0xf] = DAT_00102004;
  return;
}