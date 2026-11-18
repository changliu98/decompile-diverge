int f_to_ab(float f, int *a, int *b, int *c, int *d)
{
  float f2 = f * 255.0 / 100.0;
  *a = (int) f2 / 256;
  *b = (int) f2 % 256;
  return 2;
}