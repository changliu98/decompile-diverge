static void
process_bitmap_updates(STREAM s)
{
 int i;
 uint16 num_updates;

 logger(4, NULL, "%s()", "process_bitmap_updates");

 num_updates = *((uint16 *) s->p);
 s->p += 2;

 for (i = 0; i < num_updates; i++)
 {
  unsigned char *bmp_data;
  uint16 left, top, right, bottom, width, height, bpp, Bpp, compress, bufsize, size;
  uint16 cx, cy;

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

  cx = right - left + 1;
  cy = bottom - top + 1;

  logger(5, NULL, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compress=%d, bufsize=%d",
         left, top, right, bottom, width, height, bpp, compress, bufsize);

  if (compress == 0)
  {

   bmp_data = (unsigned char *) xmalloc(width * height * Bpp);

   int j;
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
    size = *((uint16 *) s->p);
    s->p += 2;
    s->p += 4;
   }

   bmp_data = s->p;
   s->p += size;

   bmp_data = (unsigned char *) xmalloc(width * height * Bpp);

   if (bitmap_decompress(bmp_data, width, height, bmp_data, size, Bpp))
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