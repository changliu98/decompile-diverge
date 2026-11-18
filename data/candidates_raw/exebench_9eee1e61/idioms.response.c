int get_color(float f, int *r, int *g, int *b, int *a)
{
  *r = (int)(f * 255 / 100);
  return 1;
}