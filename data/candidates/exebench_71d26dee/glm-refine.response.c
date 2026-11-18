int __cdecl obdRevConvert_2C(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  // The redundant explicit float casts are removed. 
  // The compiler implicitly handles the float arithmetic and truncation to int.
  *A = (int)((val * 255.0f) / 100.0f);
  
  // The function unconditionally returns 1 (likely indicating success)
  return 1;
}