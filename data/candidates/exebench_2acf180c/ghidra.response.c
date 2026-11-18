void unpackFloat(float aV,int *exponent,int *magnitude)

{
  int a;
  int *magnitude_local;
  int *exponent_local;
  float aV_local;
  
  *exponent = ((int)((uint)aV & 0x7f800000) >> 0x17) + -0x7f;
  *magnitude = ((uint)aV & 0x7fffff) + 0x800000;
  if (((uint)aV & 0x80000000) != 0) {
    *magnitude = -*magnitude;
  }
  return;
}