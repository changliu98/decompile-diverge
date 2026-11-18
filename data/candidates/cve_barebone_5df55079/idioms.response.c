void process_bitmap_updates(struct _STREAM s)
{
  int i;
  int num_updates = s->p[0];
  s->p += 2;
  for (i = 0; i < num_updates; i++) {
    int left = s->p[0];
    s->p += 2;
    int top = s->p[0];
    s->p += 2;
    int right = s->p[0];
    s->p += 2;
    int bottom = s->p[0];
    s->p += 2;
    int width = s->p[0];
    s->p += 2;
    int height = s->p[0];
    s->p += 2;
    int bpp = s->p[0];
    s->p += 2;
    int bpp_bits = (bpp + 7) / 8;
    int compression = s->p[0];
    s->p += 2;
    int bufsize = s->p[0];
    s->p += 2;
    int w = right - left + 1;
    int h = bottom - top + 1;
    int x = bottom;
    int y = width;
    int z = height;
    int a = bpp;
    int b = compression;
    logger(log_subject_t.Protocol, log_level_t.Debug, "%s()", "process_bitmap_updates");
    logger(log_subject_t.Graphics, log_level_t.Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d", left, top, right, x, y, z, a, b);
    if (compression == 0) {
      unsigned char *bmpdata = (uint8*)alloc_mem(bpp * width * height);
      int j;
      for (j = 0; j < height; j++) {
        copy_line(&bmpdata[(height - j - 1) * width * bpp], s->p, width * bpp);
        s->p += width * bpp;
      }
      draw_bitmap(left, top, w, h, width, height, bmpdata);
      free_mem(bmpdata);
    }
    else {
      if (compression & 0x400) {
        bufsize = bufsize;
      }
      else {
        s->p += 2;
        bufsize = s->p[0];
        s->p += 2;
        s->p += 4;
      }
      unsigned char *data = s->p;
      s->p += bufsize;
      unsigned char *bmpdata = (uint8*)alloc_mem(bpp * width * height);
      if (decompress(bmpdata, width, height, data, bufsize, bpp)) {
        draw_bitmap(left, top, w, h, width, height, bmpdata);
      }
      else {
        log_printf(log_subject_t.Graphics, log_level_t.Warning, "process_bitmap_updates(), failed to decompress bitmap");
      }
      free_mem(bmpdata);
    }
  }
}