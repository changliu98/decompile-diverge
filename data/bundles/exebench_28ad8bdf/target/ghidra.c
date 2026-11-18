void matrixApply(float *m,float x,float y,float z,float *outx,float *outy,float *outz)

{
  float *outz_local;
  float *outy_local;
  float *outx_local;
  float z_local;
  float y_local;
  float x_local;
  float *m_local;
  
  *outx = z * m[2] + x * *m + y * m[1] + m[3];
  *outy = z * m[6] + x * m[4] + y * m[5] + m[7];
  *outz = z * m[10] + x * m[8] + y * m[9] + m[0xb];
  return;
}