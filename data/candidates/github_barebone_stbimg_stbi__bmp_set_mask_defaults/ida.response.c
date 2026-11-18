int __cdecl stbi__bmp_set_mask_defaults(stbi__bmp_data *info, int compress)
{
  if ( compress == 3 )
    return 1;
  if ( compress )
    return 0;
  if ( info->bpp == 16 )
  {
    info->mr = 31744;
    info->mg = 992;
    info->mb = 31;
  }
  else if ( info->bpp == 32 )
  {
    info->mr = 16711680;
    info->mg = 65280;
    info->mb = 255;
    info->ma = -16777216;
    info->all_a = 0;
  }
  else
  {
    info->ma = 0;
    info->mb = 0;
    info->mg = 0;
    info->mr = 0;
  }
  return 1;
}