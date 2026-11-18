int stbi__bmp_set_mask_defaults(struct stbi__bmp_data *data, int compression)
{
  if (compression == 3)
    return 1;
  if (compression != 0)
    return 0;
  if (data->bpp == 16)
  {
    data->mr = 0x7C00;
    data->mg = 0x03E0;
    data->mb = 0x001F;
  }
  else if (data->bpp == 32)
  {
    data->mr = 0x00ff0000;
    data->mg = 0x0000ff00;
    data->mb = 0x000000ff;
    data->ma = 0xff000000;
    data->all_a = 0;
  }
  else
  {
    data->ma = 0;
    data->mb = 0;
    data->mg = 0;
    data->mr = 0;
  }
  return 1;
}