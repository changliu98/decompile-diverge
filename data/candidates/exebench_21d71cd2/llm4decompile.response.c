int obdRevConvert_23(float value, int *A, int *B, int *C, int *D)
{
  int intValue;

  intValue = (int)(value / 0.01);
  *A = intValue / 256;
  *B = intValue % 256;

  return 2;
}