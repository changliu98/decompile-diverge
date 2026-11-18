void process_bitmap_updates(struct stream *stream)
{
    int i;
    int num_updates = (int)stream->p[0] + (stream->p[1]<<8);
    stream->p += 2;
    for (i = 0; i < num_updates; i++) {
        int left = (int)stream->p[0] + (stream->p[1]<<8);
        stream->p += 2;
        int top = (int)stream->p[0] + (stream->p[1]<<8);
        stream->p += 2;
        int right = (int)stream->p[0] + (stream->p[1]<<8);
        stream->p += 2;
        int bottom = (int)stream->p[0] + (stream->p[1]<<8);
        stream->p += 2;
        int width = (int)stream->p[0] + (stream->p[1]<<8);
        stream->p += 2;
        int height = (int)stream->p[0] + (stream->p[1]<<8);
        stream->p += 2;
        int bpp = (int)stream->p[0] + (stream->p[1]<<8);
        stream->p += 2;
        int bpp_bytes = (bpp + 7)/8;
        int compression = (int)stream->p[0] + (stream->p[1]<<8);
        stream->p += 2;
        int size = (int)stream->p[0] + (stream->p[1]<<8);
        stream->p += 2;
        int w = right - left + 1;
        int h = bottom - top + 1;
        int x = bottom;
        int y = width;
        int w1 = height;
        int h1 = bpp;
        int c = compression;
        logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", __func__);
        logger(log_subject_t::Graphics, log_level_t::Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d", left, top, right, x, y, w1, h1, c);
        if (compression == 0) {
            unsigned char *data = (uint8*)allocate_buffer(width * height * bpp_bytes);
            int j;
            for (j = 0; j < height; j++) {
                copy_line(&data[(height - j - 1) * width * bpp_bytes], stream->p, width * bpp);
                stream->p += width * bpp;
            }
            draw_bitmap(left, top, w, h, width, height, data);
            free_buffer(data);
        }
        else if (compression & 0x400) {
            size = size;
        }
        else {
            stream->p += 2;
            size = (int)stream->p[0] + (stream->p[1]<<8);
            stream->p += 2;
            stream->p += 4;
        }
        unsigned char *data = (uint8*)stream->p;
        stream->p += size;
        unsigned char *decomp_data = (uint8*)allocate_buffer(width * height * bpp_bytes);
        if (decompress(decomp_data, width, height, data, size, bpp)) {
            draw_bitmap(left, top, w, h, width, height, decomp_data);
        }
        else {
            logger(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
        }
        free_buffer(decomp_data);
    }
}