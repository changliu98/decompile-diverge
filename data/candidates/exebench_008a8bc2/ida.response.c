int __cdecl obdRevConvert_42(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  *A = (unsigned int)(int)(float)(1000.0 * val) / 256LL;
  *B = (unsigned int)(int)(float)(1000.0 * val) % 256LL;
  return 2;
}