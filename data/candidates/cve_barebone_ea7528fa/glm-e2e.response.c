void process_bitmap_updates(STREAM *s) {
    logger(4, 0, "...", "...", 0);

    uint16_t num_updates = *(uint16_t *)s->p;
    s->p += 2;

    for (int i = 0; i < num_updates; i++) {
        uint16_t left = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t top = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t right = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t bottom = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t width = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t height = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t bpp = *(uint16_t *)s->p;
        s->p += 2;

        uint16_t line_size = (bpp + 7) / 8;

        uint16_t flags = *(uint16_t *)s->p;
        s->p += 2;
        uint16_t compressed_size = *(uint16_t *)s->p;
        s->p += 2;

        uint16_t cw = right - left + 1;
        uint16_t ch = bottom - top + 1;

        logger(5, 0, "...", left, top, right, bottom, width, height, bpp, line_size, flags, compressed_size);

        void *bitmap_data;

        if (flags == 0) {
            bitmap_data = xmalloc(width * height * line_size);
            for (int y = 0; y < height; y++) {
                memcpy(bitmap_data + (height - y - 1) * width * line_size, s->p, width * line_size);
                s->p += width * line_size;
            }
            ui_paint_bitmap(left, top, cw, ch, width, height, bitmap_data);
            xfree(bitmap_data);
        } else {
            uint16_t actual_compressed_size;
            if (flags & 0x400) {
                actual_compressed_size = compressed_size;
            } else {
                actual_compressed_size = *(uint16_t *)s->p;
                s->p += 2;
                s->p += 4; // Skip 4 bytes
            }

            uint8_t *compressed_data = s->p;
            s->p += actual_compressed_size;

            bitmap_data = xmalloc(width * height * line_size);
            if (bitmap_decompress(bitmap_data, width, height, compressed_data, actual_compressed_size, line_size)) {
                ui_paint_bitmap(left, top, cw, ch, width, height, bitmap_data);
            } else {
                logger(5, 2, "...");
            }
            xfree(bitmap_data);
        }
    }
}