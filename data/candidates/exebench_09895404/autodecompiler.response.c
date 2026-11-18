void
setblack(pixel_t rgb, pixel_t *lab,
                    colourspace_option_flags flags)
{
  colour_val_t *r, *g, *b;

  r = ((colour_val_t *) rgb);
  g = ((colour_val_t *) rgb) + 1;
  b = ((colour_val_t *) rgb) + 2;

  *r = 0;
  *g = 0;
  *b = 0;
}