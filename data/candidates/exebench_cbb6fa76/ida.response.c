int __cdecl obdRevConvert_47_4B(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  *A = (int)(float)((float)(val * 255.0) / 100.0);
  return 1;
}