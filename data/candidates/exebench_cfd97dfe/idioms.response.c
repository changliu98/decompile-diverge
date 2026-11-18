int obdRevConvert_21(float value, int *int1, int *int2, int *int3, int *int4)
{
  *int1 = (int)value / 256;
  *int2 = (int)value % 256;
  return 2;
}