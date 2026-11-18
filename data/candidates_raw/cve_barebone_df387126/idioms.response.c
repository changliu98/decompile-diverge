void process_bitmap_updates(struct stream *stream)
{
    int i;
    int num_updates = (int)stream->p[0] | (int)(stream->p[1]<<8);
    stream->p += 2;
    for (i = 0; i < num_updates; i++)
    {
        int left = (int)stream->p[0] | (int)(stream->p[1]<<8);
        stream->p += 2;
        int top = (int)stream->p[0] | (int)(stream->p[1]<<8);
        stream->p += 2;
        int right = (int)stream->p[0] | (int)(stream->p[1]<<8);
        stream->p += 2;
        int bottom = (int)stream->p[0] | (int)(stream->p[1]<<8);
        stream->p += 2;
        int width = (int)stream->p[0] | (int)(stream->p[1]<<8);
        stream->p += 2;
        int height = (int)stream->p[0] | (int)(stream->p[1]<<8);
        stream->p += 2;
        int bpp = (int)stream->p[0] | (int)(stream->p[1]<<8);
        stream->p += 2;
        int bpp_bytes = (bpp + 7)/8;
        int compression = (int)stream->p[0] | (int)(stream->p[1]<<8);
        stream->p += 2;
        int size = (int)stream->p[0] | (int)(stream->p[1]<<8);
        stream->p += 2;
        int width_ = right - left + 1;
        int height_ = bottom - top + 1;
        int x = bottom;
        int y = width;
        int h = height;
        int b = bpp_bytes;
        int c = compression;
        logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", __func__);
        logger(log_subject_t::Graphics, log_level_t::Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d",
            left, top, right, x, y, h, b, c);
        if (compression == 0)
        {
            unsigned char *bitmap = (uint8*)malloc(width*height*bpp_bytes);
            int j;
            for (j = 0; j < height; j++)
            {
                copy_line(&bitmap[width*height - (width*(j+1))], stream->p, width*bpp);
                stream->p += width*bpp;
            }
            draw_bitmap(left, top, width_, height_, width, height, bitmap);
            free(bitmap);
        }
        else
        {
            if (compression & 0x400)
            {
                size = size;
            }
            else
            {
                stream->p += 2;
                size = (int)stream->p[0] | (int)(stream->p[1]<<8);
                stream->p += 2;
                stream->p += 2;
            }
            unsigned char *data = (uint8*)stream->p;
            stream->p += size;
            unsigned char *bitmap = (uint8*)malloc(width*height*bpp_bytes);
            if (decompress_bitmap(bitmap, width, height, data, size, bpp))
            {
                draw_bitmap(left, top, width_, height_, width, height, bitmap);
            }
            else
            {
                logger(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
            }
            free(bitmap);
        }
    }
}