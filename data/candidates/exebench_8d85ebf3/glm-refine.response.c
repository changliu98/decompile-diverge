int __cdecl obdRevConvert_04(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  // The redundant float casts are removed. The compiler implicitly handles 
  // the float arithmetic, and the explicit cast to int truncates the result 
  // before assigning it to the unsigned int pointer.
  *A = (int)((val * 255.0f) / 100.0f);
  
  // Unused parameters are explicitly cast to void to indicate they are 
  // intentionally ignored, which is a common practice in reverse engineering 
  // stubs or interface conformations.
  (void)B;
  (void)C;
  (void)D;
  
  return 1;
}