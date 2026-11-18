void
process_bitmap_updates(STREAM s)
{
  int i;
  uint16 num_updates;
  uint16 left, top, right, bottom, width, height, bpp, Bpp, bufsize, size;
  uint16 compress;
  uint8 * data, * bmp_data;

  logger(4, NULL, "%s()", __FUNCTION__);

  in_uint16_le(s, num_updates);
  s->p += 2;

  for (i = 0; i < num_updates; i++)
  {
    in_uint16_le(s, left);
    s->p += 2;
    in_uint16_le(s, top);
    s->p += 2;
    in_uint16_le(s, right);
    s->p += 2;
    in_uint16_le(s, bottom);
    s->p += 2;
    in_uint16_le(s, width);
    s->p += 2;
    in_uint16_le(s, height);
    s->p += 2;
    in_uint16_le(s, bpp);
    s->p += 2;
    Bpp = (bpp + 7) / 8;
    in_uint16_le(s, compress);
    s->p += 2;
    in_uint16_le(s, bufsize);
    s->p += 2;
    if (compress & 0x0400)
    {
      size = bufsize;
    }
    else
    {
      s->p += 2;
      size = ((uint16) s->end - (uint16) s->p);
      s->p += 4;
    }

    data = s->p;
    s->p += bufsize;

    bmp_data = xmalloc(width * height * Bpp);

    if (compress == 0)
    {
      int j;
      /* Copy image data from RDP stream, note that it is bottom up! */
      for (j = 0; j < height; j++)
      {
        memcpy(bmp_data + (height - j - 1) * width * Bpp, data, width * Bpp);
        data += width * Bpp;
      }
      ui_paint_bitmap(left, top, right - left + 1, bottom - top + 1,
		       width, height, bmp_data);
      xfree(bmp_data);
    }
    else
    {
      if (bitmap_decompress(bmp_data, width, height, data, size, Bpp))
      {
        ui_paint_bitmap(left, top, right - left + 1, bottom - top + 1,
		                 width, height, bmp_data);
      }
      else
      {
        logger(5, 2, "process_bitmap_updates(), failed to decompress bitmap");
      }
      xfree(bmp_data);
    }
  }
}