void process_bitmap_updates(struct stream *stream)
{
  int i; int j;
  int num_updates;
  int left; int right; int top; int bottom;
  int width; int height;
  int bpp; int Bpp;
  int compression;
  int bufsize; int size;
  int cx; int cy;
  unsigned char *data;
  unsigned char *bmpdata;
  unsigned char *buf;
  logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", __func__);
  num_updates = (int)stream->p[0];
  stream->p += 2;
  for (i = 0; i < num_updates; i++)
  {
    left = (int)stream->p[0];
    stream->p += 2;
    top = (int)stream->p[0];
    stream->p += 2;
    right = (int)stream->p[0];
    stream->p += 2;
    bottom = (int)stream->p[0];
    stream->p += 2;
    width = (int)stream->p[0];
    stream->p += 2;
    height = (int)stream->p[0];
    stream->p += 2;
    bpp = (int)stream->p[0];
    stream->p += 2;
    Bpp = (bpp + 7) / 8;
    compression = (int)stream->p[0];
    stream->p += 2;
    bufsize = (int)stream->p[0];
    stream->p += 2;
    cx = right - left + 1;
    cy = bottom - top + 1;
    buf = (unsigned char *)stream->p + bottom * width * Bpp;
    stream->p += (width * height * Bpp);
    logger(log_subject_t::Graphics, log_level_t::Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d", left, top, right, bottom, width, height, bpp, compression);
    if (compression == 0)
    {
      bmpdata = (unsigned char *)alloc_buffer(width * height * Bpp);
      for (j = 0; j < height; j++)
      {
        copy_line(bmpdata + (height - j - 1) * width * Bpp, stream->p, width * Bpp);
        stream->p += (width * Bpp);
      }
      update_screen(left, top, cx, cy, width, height, bmpdata);
      free_buffer(bmpdata);
    }
    else
    {
      if (compression & 0x400)
      {
        size = bufsize;
      }
      else
      {
        stream->p += 2;
        size = (int)stream->p[0];
        stream->p += 2;
        stream->p += 4;
      }
      data = (unsigned char *)stream->p;
      stream->p += size;
      bmpdata = (unsigned char *)alloc_buffer(width * height * Bpp);
      if (decompress_bitmap(bmpdata, width, height, data, size, Bpp))
      {
        update_screen(left, top, cx, cy, width, height, bmpdata);
      }
      else
      {
        logger(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
      }
      free_buffer(bmpdata);
    }
  }
}