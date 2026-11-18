void process_bitmap_updates(struct stream *s)
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
    int Bpp = (bpp + 7) / 8;
    int compression = s->p[0];
    s->p += 2;
    int bufsize = s->p[0];
    s->p += 2;
    int cx = right - left + 1;
    int cy = bottom - top + 1;
    int w = width;
    int h = height;
    int b = Bpp;
    int c = compression;
    logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", "process_bitmap_updates");
    logger(log_subject_t::Graphics, log_level_t::Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d", left, top, right, bottom, w, h, b, c);
    if (compression == 0) {
      unsigned char *bmpdata = (uint8 *)malloc(width * height * Bpp);
      int y;
      for (y = 0; y < height; y++) {
        copy_line(&bmpdata[(height - y - 1) * width * Bpp], s->p, width * Bpp);
        s->p += width * Bpp;
      }
      draw_bitmap(left, top, cx, cy, width, height, bmpdata);
      free(bmpdata);
    } else if (compression & 0x400) {
      int size = bufsize;
      unsigned char *data = s->p;
      s->p += size;
      unsigned char *bmpdata = (uint8 *)malloc(width * height * Bpp);
      if (decompress(bmpdata, width, height, data, size, Bpp)) {
        draw_bitmap(left, top, cx, cy, width, height, bmpdata);
      } else {
        log_printf(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
      }
      free(bmpdata);
    } else {
      s->p += 2;
      int size = s->p[0];
      s->p += 2;
      s->p += 4;
      unsigned char *data = s->p;
      s->p += size;
      unsigned char *bmpdata = (uint8 *)malloc(width * height * Bpp);
      if (decompress(bmpdata, width, height, data, size, Bpp)) {
        draw_bitmap(left, top, cx, cy, width, height, bmpdata);
      } else {
        log_printf(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
      }
      free(bmpdata);
    }
  }
}