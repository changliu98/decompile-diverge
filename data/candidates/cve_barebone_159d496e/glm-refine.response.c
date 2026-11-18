void __cdecl process_bitmap_updates(STREAM s)
{
    uint16 *p16 = (uint16 *)s->p;
    uint16 num_updates = *p16++;
    s->p = (uint8 *)p16;

    for (int i = 0; i < num_updates; ++i)
    {
        p16 = (uint16 *)s->p;
        uint16 left     = *p16++;
        uint16 top      = *p16++;
        uint16 right    = *p16++;
        uint16 bottom   = *p16++;
        uint16 width    = *p16++;
        uint16 height   = *p16++;
        uint16 bpp      = *p16++;
        uint16 compress = *p16++;
        uint16 bufsize  = *p16++;
        s->p = (uint8 *)p16;

        uint16 Bpp  = (bpp + 7) / 8;
        uint16 cx   = right - left + 1;
        uint16 cy   = bottom - top + 1;
        uint16 size = 0;

        logger(
            log_subject_t::Graphics,
            log_level_t::Debug,
            "process_bitmap_updates(), [%d,%d,%d,%d], [%d,%d], bpp=%d, compression=%d",
            left, top, right, bottom, width, height, Bpp, compress);

        if (compress)
        {
            if ((compress & 0x400) != 0)
            {
                size = bufsize;
            }
            else
            {
                s->p += 2;
                size = *(uint16 *)s->p;
                s->p += 2;
                s->p += 4;
            }

            uint8 *data = s->p;
            s->p += size;

            uint8 *bmpdata = (uint8 *)xmalloc((size_t)Bpp * height * width);
            if (bitmap_decompress(bmpdata, width, height, data, size, Bpp))
            {
                ui_paint_bitmap(left, top, cx, cy, width, height, bmpdata);
            }
            else
            {
                logger(log_subject_t::Graphics, log_level_t::Warning, "process_bitmap_updates(), failed to decompress bitmap");
            }
            xfree(bmpdata);
        }
        else
        {
            uint8 *bmpdata = (uint8 *)xmalloc((size_t)Bpp * height * width);
            for (int y = 0; y < height; ++y)
            {
                memcpy(&bmpdata[(size_t)Bpp * width * (height - y - 1)], s->p, (size_t)Bpp * width);
                s->p += (size_t)Bpp * width;
            }
            ui_paint_bitmap(left, top, cx, cy, width, height, bmpdata);
            xfree(bmpdata);
        }
    }
}