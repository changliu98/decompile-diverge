void process_bitmap_updates(STREAM *s) {
    uint16_t num_updates;
    uint16_t left, top, right, bottom, width, height, bpp, row_size, compressed_type, compressed_len;
    uint16_t update_width, update_height;
    uint8_t *compressed_data;
    uint8_t *bitmap_data;
    int i;

    logger(4, 0, "process_bitmap_updates", "process_bitmap_updates");

    // Read num_updates
    num_updates = *(uint16_t *)s->p;
    s->p += 2;

    for (i = 0; i < num_updates; i++) {
        left = *(uint16_t *)s->p;
        s->p += 2;
        top = *(uint16_t *)s->p;
        s->p += 2;
        right = *(uint16_t *)s->p;
        s->p += 2;
        bottom = *(uint16_t *)s->p;
        s->p += 2;
        width = *(uint16_t *)s->p;
        s->p += 2;
        height = *(uint16_t *)s->p;
        s->p += 2;
        bpp = *(uint16_t *)s->p;
        s->p += 2;

        // Calculate row_size = (bpp + 7) / 8
        row_size = (bpp + 7) / 8;

        compressed_type = *(uint16_t *)s->p;
        s->p += 2;
        compressed_len = *(uint16_t *)s->p;
        s->p += 2;

        update_width = right - left + 1;
        update_height = bottom - top + 1;

        logger(5, 0, "left=%d top=%d right=%d bottom=%d width=%d height=%d bpp=%d row_size=%d compressed_type=%d compressed_len=%d",
               left, top, right, bottom, width, height, bpp, row_size, compressed_type, compressed_len);

        if (compressed_type == 0) {
            // Uncompressed bitmap
            bitmap_data = xmalloc(width * height * row_size);
            for (int j = 0; j < height; j++) {
                // Bitmaps are stored bottom-up
                memcpy(bitmap_data + (height - j - 1) * (width * row_size), s->p, width * row_size);
                s->p += width * row_size;
            }
            ui_paint_bitmap(left, top, update_width, update_height, width, height, bitmap_data);
            xfree(bitmap_data);
        } else {
            // Compressed bitmap
            if (compressed_type & 0x400) {
                // Use the previously read compressed_len
            } else {
                // Read a new compressed_len and skip 4 bytes
                compressed_len = *(uint16_t *)s->p;
                s->p += 2;
                s->p += 4;
            }
            compressed_data = s->p;
            s->p += compressed_len;

            bitmap_data = xmalloc(width * height * row_size);
            if (bitmap_decompress(bitmap_data, width, height, compressed_data, compressed_len, row_size)) {
                ui_paint_bitmap(left, top, update_width, update_height, width, height, bitmap_data);
            } else {
                logger(5, 2, "bitmap_decompress failed");
            }
            xfree(bitmap_data);
        }
    }
}