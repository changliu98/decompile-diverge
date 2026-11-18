void process_bitmap_updates(struct stream *stream)
{
    int i;
    int num_updates = stream->p[0];
    stream->p += 2;
    for (i = 0; i < num_updates; i++)
    {
        int left = stream->p[0];
        stream->p += 2;
        int top = stream->p[0];
        stream->p += 2;
        int right = stream->p[0];
        stream->p += 2;
        int bottom = stream->p[0];
        stream->p += 2;
        int width = stream->p[0];
        stream->p += 2;
        int height = stream->p[0];
        stream->p += 2;
        int bpp = stream->p[0];
        stream->p += 2;
        int Bpp = (bpp + 7) / 8;
        int compression = stream->p[0];
        stream->p += 2;
        int bufsize = stream->p[0];
        stream->p += 2;
        int cx = right - left + 1;
        int cy = bottom - top + 1;
        int x = bottom;
        int y = width;
        int h = height;
        int b = Bpp;
        int c = compression;
        logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", "process_bitmap_updates");
        logger(log_subject_t::Graphics, log_level_t::Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d", left, top, right, x, y, h, b, c);
        if (compression == 0)
        {
            unsigned char *bmpdata = (uint8 *)alloc_bitmap(width * height * Bpp);
            int j;
            for (j = 0; j < height; j++)
            {
                int len = Bpp * width;
                copy_bits(&bmpdata[(height - j - 1) * width * Bpp], stream->p, len);
                stream->p += len;
            }
            update_screen(left, top, cx, cy, width, height, bmpdata);
            free_bitmap(bmpdata);
        }
        else
        {
            if (compression & 0x400)
            {
                bufsize = bufsize;
            }
            else
            {
                stream->p += 2;
                bufsize = stream->p[0];
                stream->p += 2;
                stream->p += 4;
            }
            unsigned char *data = (uint8 *)stream->p;
            stream->p += bufsize;
            unsigned char *bmpdata = (uint8 *)alloc_bitmap(width * height * Bpp);
            if (decompress_bitmap(bmpdata, width, height, data, bufsize, Bpp))
            {
                update_screen(left, top, cx, cy, width, height, bmpdata);
            }
            else
            {
                logger(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
            }
            free_bitmap(bmpdata);
        }
    }
}