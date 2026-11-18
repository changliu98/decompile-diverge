int __cdecl stbi__tga_get_comp(int bits_per_pixel, int is_grey, int *is_rgb16)
{
  int comp;

  if (is_rgb16)
    *is_rgb16 = 0;

  switch (bits_per_pixel)
  {
    case 8:
      comp = 1;
      break;
      
    case 15:
    case 16:
      if (bits_per_pixel == 16 && is_grey)
      {
        comp = 2;
      }
      else
      {
        if (is_rgb16)
          *is_rgb16 = 1;
        comp = 3;
      }
      break;
      
    case 24:
    case 32:
      comp = bits_per_pixel / 8;
      break;
      
    default:
      comp = 0;
      break;
  }

  return comp;
}