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
        int bpp_bytes = (bpp + 7)/8;
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
        logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", __func__);
        logger(log_subject_t::Graphics, log_level_t::Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d", left, top, right, x, y, z, a, b);
        if (compression == 0) {
            unsigned char *data = (uint8 *)get_buffer(width * height * bpp);
            int j;
            for (j = 0; j < height; j++) {
                int size = bpp * width;
                int offset = (height - j - 1) * bpp * width;
                copy_data(&data[offset], s->p, size);
                s->p += size;
            }
            update_screen(left, top, w, h, width, height, data);
            free_buffer(data);
        } else {
            int size;
            if (compression & 0x0400) {
                size = bufsize;
            } else {
                s->p += 2;
                size = s->p[0];
                s->p += 2;
                s->p += 4;
            }
            unsigned char *data = s->p;
            s->p += size;
            unsigned char *decompressed = (uint8 *)get_buffer(width * height * bpp);
            if (decompress(decompressed, width, height, data, size, bpp)) {
                update_screen(left, top, w, h, width, height, decompressed);
            } else {
                log_printf(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
            }
            free_buffer(decompressed);
        }
    }
}