int C_Utils_compare_float_ptr(float *item1,float *item2)

{
  float fVar1;
  float fVar2;
  float i2;
  float i1;
  float *item2_local;
  float *item1_local;
  undefined4 local_c;
  
  fVar1 = *item1;
  fVar2 = *item2;
  if ((fVar1 != fVar2) || (NAN(fVar1) || NAN(fVar2))) {
    local_c = 1;
    if (fVar1 < fVar2) {
      local_c = -1;
    }
  }
  else {
    local_c = 0;
  }
  return local_c;
}