int __cdecl obdRevConvert_0C(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  *A = (unsigned int)(int)(float)(4.0 * val) / 256LL;
  *B = (unsigned int)(int)(float)(4.0 * val) % 256LL;
  return 2;
}