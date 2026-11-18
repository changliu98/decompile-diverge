int __cdecl obdRevConvert_52(float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D)
{
  *A = (unsigned int)((val * 255.0f) / 100.0f);
  return 1;
}