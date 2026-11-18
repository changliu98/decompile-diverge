int stbi__bmp_set_mask_defaults(stbi__bmp_data *info,int compress)

{
  int compress_local;
  stbi__bmp_data *info_local;
  int local_c;
  
  if (compress == 3) {
    local_c = 1;
  }
  else if (compress == 0) {
    if (info->bpp == 0x10) {
      info->mr = 0x7c00;
      info->mg = 0x3e0;
      info->mb = 0x1f;
    }
    else if (info->bpp == 0x20) {
      info->mr = 0xff0000;
      info->mg = 0xff00;
      info->mb = 0xff;
      info->ma = 0xff000000;
      info->all_a = 0;
    }
    else {
      info->ma = 0;
      info->mb = 0;
      info->mg = 0;
      info->mr = 0;
    }
    local_c = 1;
  }
  else {
    local_c = 0;
  }
  return local_c;
}