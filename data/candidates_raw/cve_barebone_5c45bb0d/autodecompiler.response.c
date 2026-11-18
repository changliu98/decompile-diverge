static void
process_bitmap_updates(STREAM s)
{
  int i, j;
  uint16 num_updates;
  uint16 left, top, right, bottom, width, height, bpp, Bpp, compress, bufsize, size;
  uint8 * data, * bmp_data;

  logger(4, NULL, "%s()", "process_bitmap_updates");

  num_updates = *((uint16 *) s->p);
  s->p += 2;

  for (i = 0; i < num_updates; i++)
  {
    left = *((uint16 *) s->p);
    s->p += 2;
    top = *((uint16 *) s->p);
    s->p += 2;
    right = *((uint16 *) s->p);
    s->p += 2;
    bottom = *((uint16 *) s->p);
    s->p += 2;
    width = *((uint16 *) s->p);
    s->p += 2;
    height = *((uint16 *) s->p);
    s->p += 2;
    bpp = *((uint16 *) s->p);
    s->p += 2;
    Bpp = (bpp + 7) / 8;
    compress = *((uint16 *) s->p);
    s->p += 2;
    bufsize = *((uint16 *) s->p);
    s->p += 2;

    logger(5, NULL, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compress=%d, bufsize=%d",
           left, top, right, bottom, width, height, Bpp, compress, bufsize);

    if (compress == 0)
    {
      bmp_data = (uint8 *) xmalloc(width * height * Bpp);
      for (j = 0; j < height; j++)
      {
        memcpy(bmp_data + ((height - j - 1) * width * Bpp), s->p, width * Bpp);
        s->p += width * Bpp;
      }
      ui_paint_bitmap(left, top, right - left + 1, bottom - top + 1, width, height, bmp_data);
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
        size = *((uint16 *) s->p);
        s->p += 2;
        s->p += 4;
      }

      data = s->p;
      s->p += size;

      bmp_data = (uint8 *) xmalloc(width * height * Bpp);

      if (bitmap_decompress(bmp_data, width, height, data, size, Bpp))
      {
        ui_paint_bitmap(left, top, right - left + 1, bottom - top + 1, width, height, bmp_data);
      }
      else
      {
        logger(5, 2, "process_bitmap_updates(), failed to decompress bitmap");
      }
      xfree(bmp_data);
    }
  }
}