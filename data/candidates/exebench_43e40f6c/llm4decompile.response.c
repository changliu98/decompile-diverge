int obdRevConvert_0C(float value, int *A, int *B, int *C, int *D)
{
  int32_t val = (int32_t)(value * 100);
  *A = val / 256;
  *B = val % 256;
  return 2;
}