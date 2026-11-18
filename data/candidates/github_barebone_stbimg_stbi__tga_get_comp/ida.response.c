int __cdecl stbi__tga_get_comp(int bits_per_pixel, int is_grey, int *is_rgb16)
{
  int v4; // [rsp+1Ch] [rbp-4h]

  if ( is_rgb16 )
    *is_rgb16 = 0;
  switch ( bits_per_pixel )
  {
    case 8:
      v4 = 1;
      break;
    case 15:
      goto LABEL_7;
    case 16:
      if ( is_grey )
      {
        v4 = 2;
      }
      else
      {
LABEL_7:
        if ( is_rgb16 )
          *is_rgb16 = 1;
        v4 = 3;
      }
      break;
    case 24:
    case 32:
      v4 = bits_per_pixel / 8;
      break;
    default:
      v4 = 0;
      break;
  }
  return v4;
}