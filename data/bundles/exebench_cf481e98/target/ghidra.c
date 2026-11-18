void Sqrt(float x,float *res)

{
  float fVar1;
  int i;
  float xhalf;
  float *res_local;
  float x_local;
  
  fVar1 = (float)(0x5f3759df - ((int)x >> 1));
  fVar1 = fVar1 * (-(DAT_00102008 * x * fVar1) * fVar1 + DAT_00102004);
  if (fVar1 <= 0.0) {
    *res = 0.0;
  }
  else {
    *res = DAT_0010200c / fVar1;
  }
  return;
}