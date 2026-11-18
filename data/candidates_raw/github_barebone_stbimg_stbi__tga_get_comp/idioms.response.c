int get_color_depth(int bits_per_pixel, int is_grey, int *is_rgb16)
{
  int color_depth = 0;
  if (is_rgb16 != ((void *)0))
    *is_rgb16 = 0;
  switch (bits_per_pixel) {
    case 8:
      color_depth = 1;
      break;
    case 16:
      if (is_grey)
        color_depth = 2;
      else {
        if (is_rgb16 != ((void *)0))
          *is_rgb16 = 1;
        color_depth = 3;
      }
      break;
    case 15:
      if (is_rgb16 != ((void *)0))
        *is_rgb16 = 1;
      color_depth = 3;
      break;
    case 24:
    case 32:
      color_depth = bits_per_pixel / 8;
      break;
    default:
      color_depth = 0;
      break;
  }
  return (color_depth);
}