static void
process_bitmap_updates(STREAM s)
{
  int i, j;
  uint16 num_updates, left, top, right, bottom, width, height, bpp, Bpp,
         compress, bufsize, size, cx, cy;
  uint8 * data, * bmp_data;

  logger(4, NULL, "%s()", "process_bitmap_updates");

  num_updates = (*s->p);
  s->p += 2;

  for (i = 0; i < num_updates; i++)
  {
    left = (*s->p);
    s->p += 2;
    top = (*s->p);
    s->p += 2;
    right = (*s->p);
    s->p += 2;
    bottom = (*s->p);
    s->p += 2;
    width = (*s->p);
    s->p += 2;
    height = (*s->p);
    s->p += 2;
    bpp = (*s->p);
    s->p += 2;
    Bpp = (bpp + 7) / 8;
    compress = (*s->p);
    s->p += 2;
    bufsize = (*s->p);
    s->p += 2;

    cx = right - left + 1;
    cy = bottom - top + 1;

    logger(5, NULL, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compress=%d, bufsize=%d",
           left, top, right, bottom, width, height, bpp, compress, bufsize);

    if (compress == 0)
    {
      bmp_data = (uint8 *) xmalloc(width * height * Bpp);
      for (j = 0; j < height; j++)
      {
        memcpy(bmp_data + ((height - j - 1) * width * Bpp), s->p, width * Bpp);
        s->p += width * Bpp;
      }
      ui_paint_bitmap(left, top, cx, cy, width, height, bmp_data);
      xfree(bmp_data);
    }
    else
    {
      if (compress & 0x0400)
      {
        size = bufsize;
      }
      else
      {
        s->p += 2;
        size = (*s->p);
        s->p += 2;
        s->p += 4;
      }

      data = s->p;
      s->p += size;

      bmp_data = (uint8 *) xmalloc(width * height * Bpp);

      if (bitmap_decompress(bmp_data, width, height, data, size, Bpp))
      {
        ui_paint_bitmap(left, top, cx, cy, width, height, bmp_data);
      }
      else
      {
        logger(5, 2, "process_bitmap_updates(), failed to decompress bitmap");
      }
      xfree(bmp_data);
    }
  }
}