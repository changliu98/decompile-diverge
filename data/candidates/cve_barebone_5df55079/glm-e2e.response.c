void process_bitmap_updates(uint8_t **s) {
    uint16_t num_updates;
    uint16_t left, top, right, bottom, width, height, bpp;
    uint16_t bytes_per_row, compressed_type, compressed_len;
    uint16_t update_width, update_height;
    uint8_t *compressed_data;
    uint8_t *bitmap_data;
    int i;

    logger(4, 0, "process_bitmap_updates\n");

    num_updates = *(uint16_t*)(*s);
    *s += 2;

    for (i = 0; i < num_updates; i++) {
        left = *(uint16_t*)(*s);
        *s += 2;
        top = *(uint16_t*)(*s);
        *s += 2;
        right = *(uint16_t*)(*s);
        *s += 2;
        bottom = *(uint16_t*)(*s);
        *s += 2;
        width = *(uint16_t*)(*s);
        *s += 2;
        height = *(uint16_t*)(*s);
        *s += 2;
        bpp = *(uint16_t*)(*s);
        *s += 2;

        // Equivalent to (bpp + 7) / 8
        bytes_per_row = (bpp + 7) / 8;
        
        compressed_type = *(uint16_t*)(*s);
        *s += 2;
        compressed_len = *(uint16_t*)(*s);
        *s += 2;

        update_width = right - left + 1;
        update_height = bottom - top + 1;

        logger(5, 0, "left=%d top=%d right=%d bottom=%d width=%d height=%d bpp=%d bytes_per_row=%d compressed_type=%d compressed_len=%d\n",
               left, top, right, bottom, width, height, bpp, bytes_per_row, compressed_type, compressed_len);

        if (compressed_type == 0) {
            // Uncompressed bitmap
            bitmap_data = xmalloc(width * height * bytes_per_row);
            for (int j = 0; j < height; j++) {
                // Bitmaps are typically stored bottom-up
                memcpy(bitmap_data + (height - j - 1) * (width * bytes_per_row), *s, width * bytes_per_row);
                *s += width * bytes_per_row;
            }
            ui_paint_bitmap(left, top, update_width, update_height, width, height, bitmap_data);
            xfree(bitmap_data);
        } else {
            // Compressed bitmap
            if (compressed_type & 0x400) {
                // Length is already provided in compressed_len
            } else {
                compressed_len = *(uint16_t*)(*s);
                *s += 2;
                // Skip 4 bytes (likely reserved/padding)
                *s += 4;
            }
            
            compressed_data = *s;
            *s += compressed_len;

            bitmap_data = xmalloc(width * height * bytes_per_row);
            if (bitmap_decompress(bitmap_data, width, height, compressed_data, compressed_len, bytes_per_row)) {
                ui_paint_bitmap(left, top, update_width, update_height, width, height, bitmap_data);
            } else {
                logger(5, 2, "bitmap_decompress failed\n");
            }
            xfree(bitmap_data);
        }
    }
}