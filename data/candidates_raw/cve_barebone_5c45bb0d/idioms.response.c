void process_bitmap_updates(struct stream *stream)
{
  int i;
  int num_updates;
  int left; int right; int top; int bottom;
  int width; int height;
  int bpp; int Bpp; int compress; int bufsize;
  int cx; int cy;
  unsigned char *data;
  unsigned char *buf;
  unsigned char *bmpdata;
  logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", __func__);
  num_updates = (int)(stream->p)[0] | ((int)(stream->p)[1]<<8);
  stream->p += 2;
  for (i = 0; i < num_updates; i++)
  {
    left = (int)(stream->p)[0] | ((int)(stream->p)[1]<<8);
    stream->p += 2;
    top = (int)(stream->p)[0] | ((int)(stream->p)[1]<<8);
    stream->p += 2;
    right = (int)(stream->p)[0] | ((int)(stream->p)[1]<<8);
    stream->p += 2;
    bottom = (int)(stream->p)[0] | ((int)(stream->p)[1]<<8);
    stream->p += 2;
    width = (int)(stream->p)[0] | ((int)(stream->p)[1]<<8);
    stream->p += 2;
    height = (int)(stream->p)[0] | ((int)(stream->p)[1]<<8);
    stream->p += 2;
    bpp = (int)(stream->p)[0] | ((int)(stream->p)[1]<<8);
    stream->p += 2;
    Bpp = (bpp + 7)/8;
    compress = (int)(stream->p)[0] | ((int)(stream->p)[1]<<8);
    stream->p += 2;
    bufsize = (int)(stream->p)[0] | ((int)(stream->p)[1]<<8);
    stream->p += 2;
    cx = right - left + 1;
    cy = bottom - top + 1;
    logger(log_subject_t::Graphics, log_level_t::Debug,
        "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d",
        left, top, right, bottom, width, height, bpp, compress);
    if (compress == 0)
    {
      bmpdata = (unsigned char *)alloc_framebuffer(width * height * Bpp);
      for (int y = 0; y < height; y++)
      {
        stream2framebuffer(&bmpdata[(height - y - 1)*width*Bpp], stream->p, width * Bpp);
        stream->p += width * Bpp;
      }
      draw_framebuffer(left, top, cx, cy, width, height, bmpdata);
      free_framebuffer(bmpdata);
    }
    else if (compress & 0x400)
    {
      int size = bufsize;
      data = stream->p;
      stream->p += size;
      buf = (unsigned char *)alloc_framebuffer(width * height * Bpp);
      if (decompress(buf, width, height, data, size, Bpp))
      {
        draw_framebuffer(left, top, cx, cy, width, height, buf);
      }
      else
      {
        log_printf(log_subject_t::Graphics, log_level_t::Warning,
            "process_bitmap_updates(), failed to decompress bitmap");
      }
      free_framebuffer(buf);
    }
    else
    {
      int size = (int)(stream->p)[0] | ((int)(stream->p)[1]<<8);
      stream->p += 2;
      data = (unsigned char *)stream->p;
      stream->p += size;
      stream->p += 4;
      buf = (unsigned char *)alloc_framebuffer(width * height * Bpp);
      if (decompress(buf, width, height, data, size, Bpp))
      {
        draw_framebuffer(left, top, cx, cy, width, height, buf);
      }
      else
      {
        log_printf(log_subject_t::Graphics, log_level_t::Warning,
            "process_bitmap_updates(), failed to decompress bitmap");
      }
      free_framebuffer(buf);
    }
  }
}