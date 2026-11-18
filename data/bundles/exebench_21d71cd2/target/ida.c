int __cdecl obdRevConvert_23(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  *A = (unsigned int)(int)(float)(val / 10.0) / 256LL;
  *B = (unsigned int)(int)(float)(val / 10.0) % 256LL;
  return 2;
}