void drmp3_L3_idct3(float x0,float x1,float x2,float *dst)

{
  float fVar1;
  float fVar2;
  float a1;
  float m1;
  float *dst_local;
  float x2_local;
  float x1_local;
  float x0_local;
  
  fVar1 = DAT_00102024 * x1;
  fVar2 = -x2 * DAT_00102020 + x0;
  dst[1] = x0 + x2;
  *dst = fVar2 + fVar1;
  dst[2] = fVar2 - fVar1;
  return;
}