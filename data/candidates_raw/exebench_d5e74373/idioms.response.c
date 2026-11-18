int f_to_ab(float f, int *a, int *b, int *c, int *d)
{
  float f1 = f + 40.0f;
  float f2 = f1 * 10.0f;
  *a = (int) f2 / 256;
  *b = (int) f2 % 256;
  return 2;
}