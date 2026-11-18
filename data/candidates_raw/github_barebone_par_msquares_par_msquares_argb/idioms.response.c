static unsigned int get_color(unsigned char *data, int bpp)
{
  int color = 0;
  if (bpp == 4)
    return (data[0] << 16) | (data[1] << 8) | (data[2] << 0) | (data[3] << 24);
  for (int i = 0; i < bpp; i++)
    color = (color << 8) | data[i];
  return color;
}