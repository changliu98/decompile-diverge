int obdRevConvert_47_4B(float color, int *red, int *green, int *blue, int *alpha)
{
  *red = (int)(color * 255.0 / 100);
  return 1;
}