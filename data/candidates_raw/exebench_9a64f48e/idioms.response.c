int set_alpha(struct _color *color, float alpha)
{
  color->alpha = alpha;
  if (alpha < 0.0) {
    color->red = 0.0;
    color->green = 255.0;
    if (alpha == -2.0) {
      color->blue = 0.0;
      color->alpha = -1.0;
    } else {
      color->blue = 2.0;
    }
  } else {
    color->red = alpha;
    color->green = alpha;
    color->alpha = alpha;
  }
  return 0;
}