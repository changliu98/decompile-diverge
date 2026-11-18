void process_bitmap_updates(struct stream *s)
{
    int i; int j;
    int num_updates = s->p[0];
    s->p += 2;
    for (i = 0; i < num_updates; i++)
    {
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
        int bpp_per_byte = (bpp + 7) / 8;
        int compression = s->p[0];
        s->p += 2;
        int bufsize = s->p[0];
        s->p += 2;
        int width_inc = right - left + 1;
        int height_inc = bottom - top + 1;
        int width_inc2 = width_inc * bpp_per_byte;
        int height_inc2 = height_inc * bpp_per_byte;
        int width2 = width * bpp_per_byte;
        int height2 = height * bpp_per_byte;
        logger(log_subject_t::Protocol, log_level_t::Debug, "%s()", "process_bitmap_updates");
        logger(log_subject_t::Graphics, log_level_t::Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d",
            left, top, right, bottom, width, height, bpp, compression);
        if (compression == 0)
        {
            unsigned char *data = (uint8 *)malloc(width * height * bpp_per_byte);
            for (j = 0; j < height; j++)
            {
                int offset = (height - j - 1) * width * bpp_per_byte;
                int size = bpp * width;
                memcpy(&data[offset], s->p, size);
                s->p += size;
            }
            update_screen(left, top, width_inc, height_inc, width, height, data);
            free(data);
        }
        else if (compression & 0x400)
        {
            int size = bufsize;
            unsigned char *data = s->p;
            s->p += size;
            unsigned char *decomp = (uint8 *)malloc(width * height * bpp_per_byte);
            if (decompress(decomp, width, height, data, size, bpp))
            {
                update_screen(left, top, width_inc, height_inc, width, height, decomp);
            }
            else
            {
                logger(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
            }
            free(decomp);
        }
        else
        {
            int size = s->p[0];
            s->p += 2;
            unsigned char *data = s->p;
            s->p += size;
            int size2 = s->p[0];
            s->p += 2;
            int size3 = s->p[0];
            s->p += 2;
            unsigned char *decomp = (uint8 *)malloc(width * height * bpp_per_byte);
            if (decompress(decomp, width, height, data, size, bpp))
            {
                update_screen(left, top, width_inc, height_inc, width, height, decomp);
            }
            else
            {
                logger(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
            }
            free(decomp);
        }
    }
}