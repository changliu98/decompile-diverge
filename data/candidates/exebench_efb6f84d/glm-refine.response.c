int __cdecl obdRevConvert_2D(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  // OBD-II Standard Scaling: (val + 100.0) / 0.78125
  // 0.78125 is exactly 100 / 128, which is a common 8-bit OBD-II resolution factor.
  *A = (unsigned int)((val + 100.0f) * 1.28f);
  
  return 1;
}