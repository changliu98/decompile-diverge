int get_color(float f, int *red, int *green, int *blue, int *alpha)
{
  float f1 = f * 255 / 100;
  *red = (int) f1;
  *green = (int) f1;
  *blue = (int) f1;
  *alpha = (int) f1;
  return 1;
}