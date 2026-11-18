int stbi__bmp_set_mask_defaults(stbi__bmp_data *info, int compress)
{
   if (compress == 3)
      return 1;
   else if (compress)
      return 0;

   if (info->bpp == 16) {
      info->mr = 0x7C00;
      info->mg = 0x03E0;
      info->mb = 0x001F;
   } else if (info->bpp == 32) {
      info->mr = 0xFF0000;
      info->mg = 0x00FF00;
      info->mb = 0x0000FF;
      info->ma = 0xFF000000;
      info->all_a = 0;
   } else {
      info->mr = info->mg = info->mb = info->ma = 0;
   }

   return 1;
}