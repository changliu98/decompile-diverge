int __cdecl obdRevConvert_2D(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  *A = (int)(float)((float)(val + 100.0) / 0.78125);
  return 1;
}