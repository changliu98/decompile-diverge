int get_color(float f, unsigned int *r, unsigned int *g, unsigned int *b, unsigned int *a)
{
  int i = (int)(f * 4);
  *r = i / 256;
  *g = i % 256;
  return 2;
}