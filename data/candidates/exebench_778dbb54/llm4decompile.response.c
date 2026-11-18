int obdRevConvert_43(float value, int *A, int *B, int *C, int *D)
{
  int32_t val;
  val = (int32_t)(value * 256 / 100);
  *A = val / 256;
  *B = val % 256;
  return 2;
}