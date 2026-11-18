float xCorrCoef(float *target,float *regressor,int subl)

{
  float ftmp2;
  float ftmp1;
  int i;
  int subl_local;
  float *regressor_local;
  float *target_local;
  float local_c;
  
  ftmp1 = 0.0;
  ftmp2 = 0.0;
  for (i = 0; i < subl; i = i + 1) {
    ftmp1 = target[i] * regressor[i] + ftmp1;
    ftmp2 = regressor[i] * regressor[i] + ftmp2;
  }
  if (ftmp1 <= 0.0) {
    local_c = 0.0;
  }
  else {
    local_c = (ftmp1 * ftmp1) / ftmp2;
  }
  return local_c;
}