int get_color(float f, int *r, int *g, int *b, int *a)
{
  *r = (int) f / 256;
  *g = (int) f % 256;
  return 2;
}