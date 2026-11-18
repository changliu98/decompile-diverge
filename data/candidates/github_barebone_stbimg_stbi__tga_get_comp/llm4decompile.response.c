int stbi__tga_get_comp(int bits_per_pixel, int is_grey, int *is_rgb16)
{
   if (is_rgb16) *is_rgb16 = 0;
   switch (bits_per_pixel) {
      case 8: return 1;
      case 15:
         if (is_grey) return 2;
      case 16:
         if (is_rgb16) *is_rgb16 = 1;
         return 3;
      case 24:
         return 3;
      case 32:
         return 4;
      default: return 0;
   }
}