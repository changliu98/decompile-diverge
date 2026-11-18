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
        int bpp2 = (bpp + 7)/8;
        int compression = s->p[0];
        s->p += 2;
        int size = s->p[0];
        s->p += 2;
        int w = right - left + 1;
        int h = bottom - top + 1;
        int x = bottom;
        int y = width;
        int z = height;
        int a = bpp2;
        int b = compression;
        logger(log_subject_t.Protocol, log_level_t.Debug, "%s()", "process_bitmap_updates");
        logger(log_subject_t.Graphics, log_level_t.Debug, "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d", left, top, right, x, y, z, a, b);
        if (compression == 0)
        {
            unsigned char *bitmap = (uint8*)get_buffer(width*height*bpp2);
            for (j = 0; j < height; j++)
            {
                copy_line(&bitmap[(height-j-1)*width*bpp2], s->p, width*bpp2);
                s->p += width*bpp2;
            }
            draw_bitmap(left, top, w, h, width, height, bitmap);
            free_buffer(bitmap);
        }
        else
        {
            if (compression & 0x400)
            {
                size = size;
            }
            else
            {
                s->p += 2;
                size = s->p[0];
                s->p += 2;
                s->p += 4;
            }
            unsigned char *data = s->p;
            s->p += size;
            unsigned char *bitmap = (uint8*)get_buffer(width*height*bpp2);
            if (decompress(bitmap, width, height, data, size, bpp2))
            {
                draw_bitmap(left, top, w, h, width, height, bitmap);
            }
            else
            {
                logger(log_subject_t.Graphics, log_level_t.Warning, "process_bitmap_updates(), failed to decompress bitmap");
            }
            free_buffer(bitmap);
        }
    }
}