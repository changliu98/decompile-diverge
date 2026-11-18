void process_bitmap_updates(struct stream *stream)
{
  int i;
  int num_updates;
  int left; int right; int top; int bottom;
  int width; int height;
  int bpp; int Bpp;
  int bufsize; int size;
  int cx; int cy;
  unsigned char *data;
  unsigned char *bmpdata;
  logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", __func__);
  num_updates = (stream->p)[0] | ((stream->p)[1] << 8);
  stream->p += 2;
  for (i = 0; i < num_updates; i++) {
    left = (stream->p)[0] | ((stream->p)[1] << 8);
    stream->p += 2;
    top = (stream->p)[0] | ((stream->p)[1] << 8);
    stream->p += 2;
    right = (stream->p)[0] | ((stream->p)[1] << 8);
    stream->p += 2;
    bottom = (stream->p)[0] | ((stream->p)[1] << 8);
    stream->p += 2;
    width = (stream->p)[0] | ((stream->p)[1] << 8);
    stream->p += 2;
    height = (stream->p)[0] | ((stream->p)[1] << 8);
    stream->p += 2;
    bpp = (stream->p)[0] | ((stream->p)[1] << 8);
    stream->p += 2;
    Bpp = (bpp + 7)/8;
    bufsize = (stream->p)[0] | ((stream->p)[1] << 8);
    stream->p += 2;
    size = (stream->p)[0] | ((stream->p)[1] << 8);
    stream->p += 2;
    stream->p += 2;
    cx = right - left + 1;
    cy = bottom - top + 1;
    logger(log_subject_t::Graphics, log_level_t::Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d", left, top, right, bottom, width, height, Bpp, bufsize);
    if (bufsize == 0) {
      bmpdata = (unsigned char *) alloc_framebuffer(width * height * Bpp);
      for (int y = 0; y < height; y++) {
        read_line(bmpdata + (width * height - y * width - y * Bpp), stream->p, width * Bpp);
        stream->p += width * Bpp;
      }
      draw_framebuffer(left, top, cx, cy, width, height, bmpdata);
      free_framebuffer(bmpdata);
    }
    else {
      if (bufsize & 0x400) {
        size = bufsize;
      }
      else {
        stream->p += 2;
        size = (stream->p)[0] | ((stream->p)[1] << 8);
        stream->p += 2;
        stream->p += 2;
      }
      data = (unsigned char *) stream->p;
      stream->p += size;
      bmpdata = (unsigned char *) alloc_framebuffer(width * height * Bpp);
      if (decompress(bmpdata, width, height, data, size, Bpp)) {
        draw_framebuffer(left, top, cx, cy, width, height, bmpdata);
      }
      else {
        logger(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
      }
      free_framebuffer(bmpdata);
    }
  }
}