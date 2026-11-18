/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int func0(float a,float b,float c)

{
  float c_local;
  float b_local;
  float a_local;
  undefined4 local_c;
  
  if ((((double)((ulong)(double)(-c * c + a * a + b * b) & _DAT_00102010) < DAT_00102008) ||
      ((double)((ulong)(double)(-b * b + a * a + c * c) & _DAT_00102010) < DAT_00102008)) ||
     ((double)((ulong)(double)(-a * a + b * b + c * c) & _DAT_00102010) < DAT_00102008)) {
    local_c = 1;
  }
  else {
    local_c = 0;
  }
  return local_c;
}