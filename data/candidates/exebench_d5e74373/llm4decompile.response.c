int obdRevConvert_3C_3F(float value, int *A, int *B, int *C, int *D)
{
  value += 128.0f;
  value /= 2.0f;
  value *= 256.0f;
  *A = (int)value / 256;
  *B = (int)value % 256;
  return 2;
}