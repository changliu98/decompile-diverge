float func0(float a,float b,float c)

{
  float fVar1;
  float area;
  float s;
  float c_local;
  float b_local;
  float a_local;
  undefined4 local_c;
  
  if (((a + b <= c) || (a + c <= b)) || (b + c <= a)) {
    local_c = DAT_0010200c;
  }
  else {
    fVar1 = (a + b + c) / DAT_00102008;
    fVar1 = sqrtf(fVar1 * (fVar1 - a) * (fVar1 - b) * (fVar1 - c));
    local_c = roundf(DAT_00102004 * fVar1);
    local_c = local_c / DAT_00102004;
  }
  return local_c;
}