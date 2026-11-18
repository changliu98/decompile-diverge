int stbi__tga_get_comp(int bits_per_pixel,int is_grey,int *is_rgb16)

{
  int *is_rgb16_local;
  int is_grey_local;
  int bits_per_pixel_local;
  int local_c;
  
  if (is_rgb16 != (int *)0x0) {
    *is_rgb16 = 0;
  }
  switch(bits_per_pixel) {
  case 8:
    local_c = 1;
    break;
  default:
    local_c = 0;
    break;
  case 0x10:
    if (is_grey != 0) {
      return 2;
    }
  case 0xf:
    if (is_rgb16 != (int *)0x0) {
      *is_rgb16 = 1;
    }
    local_c = 3;
    break;
  case 0x18:
  case 0x20:
    local_c = bits_per_pixel / 8;
  }
  return local_c;
}