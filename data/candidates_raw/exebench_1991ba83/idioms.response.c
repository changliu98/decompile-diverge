int sios_color_to_rgb(float color, int *r, int *g, int *b, int *a)
{
  *r = (int)(color * 255.0 / 100);
  return 1;
}