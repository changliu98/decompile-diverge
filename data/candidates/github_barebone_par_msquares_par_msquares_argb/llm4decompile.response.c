uint32_t par_msquares_argb(par_byte *pdata, int bpp)
{
  uint32_t color = 0;
  if (bpp == 4)
    color = (((uint32_t)pdata[3])<<24) | (((uint32_t)pdata[0])<<16) | (((uint32_t)pdata[1])<<8) | (((uint32_t)pdata[2])<<0);
  else
  {
    int i;
    for (i = 0; i < bpp; i++)
      color = (color << 8) | pdata[i];
  }
  return color;
}