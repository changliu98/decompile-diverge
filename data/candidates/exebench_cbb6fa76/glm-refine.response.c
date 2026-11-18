int __cdecl obdRevConvert_47_4B(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  // The redundant explicit float casts are removed. The compiler inherently 
  // promotes 255.0 and 100.0 to float, and the result is explicitly truncated 
  // to an integer before being assigned to the unsigned int pointer.
  *A = (int)((val * 255.0f) / 100.0f);
  
  // The function unconditionally returns 1 (likely indicating success)
  return 1;
}