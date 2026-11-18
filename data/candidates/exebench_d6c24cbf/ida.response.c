int __cdecl obdRevConvert_31(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  *A = (unsigned int)(int)val / 256LL;
  *B = (unsigned int)(int)val % 256LL;
  return 2;
}