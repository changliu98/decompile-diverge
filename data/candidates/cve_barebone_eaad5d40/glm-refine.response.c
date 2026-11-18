void __cdecl process_bitmap_updates(STREAM s)
{
  uint16_t *p16;
  uint8_t *bmpdata;
  uint8_t *data;
  uint16_t num_updates;
  uint16_t left, top, right, bottom, width, height, bpp, Bpp, compress, bufsize, size;
  uint16_t cx, cy;
  int y, i;

  logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", "process_bitmap_updates");
  
  p16 = (uint16_t *)s->p;
  num_updates = *p16++;
  
  for (i = 0; i < num_updates; ++i)
  {
    left = *p16++;
    top = *p16++;
    right = *p16++;
    bottom = *p16++;
    width = *p16++;
    height = *p16++;
    bpp = *p16++;
    Bpp = (bpp + 7) / 8;
    compress = *p16++;
    bufsize = *p16++;
    
    cx = right - left + 1;
    cy = bottom - top + 1;
    
    logger(
      log_subject_t::Graphics,
      log_level_t::Debug,
      "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d",
      left,
      top,
      right,
      bottom,
      width,
      height,
      Bpp,
      compress);
      
    if (compress)
    {
      if ((compress & 0x400) != 0)
      {
        size = bufsize;
      }
      else
      {
        p16 += 4; // Skip 8 bytes (2 + 2 + 4)
        size = *p16++;
        p16 += 2; // Skip 4 bytes
      }
      
      data = (uint8_t *)p16;
      p16 += size / 2; // Advance pointer by 'size' bytes
      
      bmpdata = (uint8_t *)xmalloc((size_t)Bpp * height * width);
      if (bitmap_decompress(bmpdata, width, height, data, size, Bpp))
      {
        ui_paint_bitmap(left, top, cx, cy, width, height, bmpdata);
      }
      else
      {
        logger(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
      }
      xfree(bmpdata);
    }
    else
    {
      bmpdata = (uint8_t *)xmalloc((size_t)Bpp * height * width);
      for (y = 0; y < height; ++y)
      {
        memcpy(&bmpdata[(size_t)Bpp * width * (height - y - 1)], p16, (size_t)Bpp * width);
        p16 = (uint16_t *)((uint8_t *)p16 + Bpp * width);
      }
      ui_paint_bitmap(left, top, cx, cy, width, height, bmpdata);
      xfree(bmpdata);
    }
  }
  
  s->p = (uint8_t *)p16;
}