void process_bitmap_updates(uint8_t **s) {
    uint16_t num_updates;
    uint16_t left, top, right, bottom, width, height, bpp, line_size, flags, in_size;
    uint16_t out_width, out_height, bytes_per_pixel;
    uint8_t *data;
    int i;

    logger(4, 0, "process_bitmap_updates\n");

    // Read 2 bytes from the stream
    num_updates = *(uint16_t*)*s;
    *s += 2;

    for (i = 0; i < num_updates; i++) {
        left = *(uint16_t*)*s;
        *s += 2;
        top = *(uint16_t*)*s;
        *s += 2;
        right = *(uint16_t*)*s;
        *s += 2;
        bottom = *(uint16_t*)*s;
        *s += 2;
        width = *(uint16_t*)*s;
        *s += 2;
        height = *(uint16_t*)*s;
        *s += 2;
        bpp = *(uint16_t*)*s;
        *s += 2;

        // Equivalent to: (bpp + 7) / 8
        bytes_per_pixel = (bpp + 7) / 8;

        line_size = *(uint16_t*)*s;
        *s += 2;
        flags = *(uint16_t*)*s;
        *s += 2;

        out_width = right - left + 1;
        out_height = bottom - top + 1;

        logger(5, 0, "bitmap: l=%d t=%d r=%d b=%d w=%d h=%d bpp=%d line=%d flags=%d\n",
               left, top, right, bottom, width, height, bpp, line_size, flags);

        if (flags == 0) {
            // Uncompressed bitmap data
            data = xmalloc(width * height * bytes_per_pixel);
            for (int j = 0; j < height; j++) {
                // Copy row by row, starting from the bottom row
                memcpy(data + (height - j - 1) * (width * bytes_per_pixel), *s, width * bytes_per_pixel);
                *s += width * bytes_per_pixel;
            }
            ui_paint_bitmap(left, top, out_width, out_height, width, height, data);
            xfree(data);
        } else {
            // Compressed bitmap data
            if (flags & 0x400) {
                in_size = line_size;
            } else {
                in_size = *(uint16_t*)*s;
                *s += 2;
                *s += 4; // Skip 4 bytes (likely reserved/padding)
            }

            data = *s;
            *s += in_size;

            uint8_t *out = xmalloc(width * height * bytes_per_pixel);
            if (bitmap_decompress(out, width, height, data, in_size, bytes_per_pixel) != 0) {
                ui_paint_bitmap(left, top, out_width, out_height, width, height, out);
            } else {
                logger(5, 2, "process_bitmap_updates: bitmap_decompress failed\n");
            }
            xfree(out);
        }
    }
}