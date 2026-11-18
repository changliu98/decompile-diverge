int __cdecl obdRevConvert_34_3B(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  *A = (unsigned int)(int)(float)(val / 0.000030499999) / 256LL;
  *B = (unsigned int)(int)(float)(val / 0.000030499999) % 256LL;
  return 2;
}