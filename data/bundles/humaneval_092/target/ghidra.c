int func0(float a,float b,float c)

{
  float fVar1;
  float c_local;
  float b_local;
  float a_local;
  int local_c;
  
  fVar1 = roundf(a);
  if ((fVar1 != a) || (NAN(fVar1) || NAN(a))) {
    local_c = 0;
  }
  else {
    fVar1 = roundf(b);
    if ((fVar1 != b) || (NAN(fVar1) || NAN(b))) {
      local_c = 0;
    }
    else {
      fVar1 = roundf(c);
      if ((fVar1 != c) || (NAN(fVar1) || NAN(c))) {
        local_c = 0;
      }
      else if ((((a + b == c) && (!NAN(a + b) && !NAN(c))) ||
               ((a + c == b && (!NAN(a + c) && !NAN(b))))) ||
              ((b + c == a && (!NAN(b + c) && !NAN(a))))) {
        local_c = 1;
      }
      else {
        local_c = 0;
      }
    }
  }
  return local_c;
}