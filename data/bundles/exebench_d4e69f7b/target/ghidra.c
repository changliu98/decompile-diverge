void warp_mat4_fill_identity(float *matrix)

{
  float *matrix_local;
  
  *matrix = DAT_00102004;
  matrix[1] = 0.0;
  matrix[2] = 0.0;
  matrix[3] = 0.0;
  matrix[4] = 0.0;
  matrix[5] = DAT_00102004;
  matrix[6] = 0.0;
  matrix[7] = 0.0;
  matrix[8] = 0.0;
  matrix[9] = 0.0;
  matrix[10] = DAT_00102004;
  matrix[0xb] = 0.0;
  matrix[0xc] = 0.0;
  matrix[0xd] = 0.0;
  matrix[0xe] = 0.0;
  matrix[0xf] = DAT_00102004;
  return;
}