int UnpackImmediate(unsigned int val, int *outByte, int *outShift)
{
  int i;
  if (val == 0)
  {
    *outByte = 0;
    *outShift = 0;
    return 1;
  }
  for (i = 0; i < 15; i++)
  {
    if (val & 0x3 && val < 0x100)
    {
      *outByte = val;
      *outShift = i;
      return 1;
    }
    if (val & 0x3)
      return 0;
    val >>= 2;
  }
  return 0;
}