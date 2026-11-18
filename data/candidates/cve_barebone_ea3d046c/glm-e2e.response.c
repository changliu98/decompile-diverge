void process_bitmap_updates(uint8_t **s) {
    uint16_t num_updates = *(uint16_t *)*s;
    *s += 2;

    logger(4, 0, "%d bitmap updates");

    for (int i = 0; i < num_updates; i++) {
        uint16_t left = *(uint16_t *)*s;
        *s += 2;
        uint16_t top = *(uint16_t *)*s;
        *s += 2;
        uint16_t right = *(uint16_t *)*s;
        *s += 2;
        uint16_t bottom = *(uint16_t *)*s;
        *s += 2;
        uint16_t bmp_width = *(uint16_t *)*s;
        *s += 2;
        uint16_t bmp_height = *(uint16_t *)*s;
        *s += 2;
        uint16_t bpp = *(uint16_t *)*s;
        *s += 2;
        
        // Equivalent to (bpp + 7) / 8
        uint16_t bytes_per_row = (bpp + 7) / 8;
        
        uint16_t flags = *(uint16_t *)*s;
        *s += 2;
        uint16_t compressed_size = *(uint16_t *)*s;
        *s += 2;

        uint16_t width = right - left + 1;
        uint16_t height = bottom - top + 1;

        logger(5, 0, "l=%d t=%d r=%d b=%d w=%d h=%d bpp=%d bytes_per_row=%d flags=%d compressed_size=%d",
               left, top, right, bottom, bmp_width, bmp_height, bpp, bytes_per_row, flags, compressed_size);

        uint8_t *bitmap_data;
        if (flags == 0) {
            // Uncompressed bitmap
            bitmap_data = xmalloc(bmp_width * bmp_height * bytes_per_row);
            for (int y = 0; y < bmp_height; y++) {
                // Bitmaps are typically stored bottom-up
                uint8_t *dst = bitmap_data + (bmp_height - y - 1) * (bmp_width * bytes_per_row);
                memcpy(dst, *s, bmp_width * bytes_per_row);
                *s += bmp_width * bytes_per_row;
            }
            ui_paint_bitmap(left, top, width, height, bmp_width, bmp_height, bitmap_data);
            xfree(bitmap_data);
        } else {
            // Compressed bitmap
            uint16_t actual_compressed_size;
            if (flags & 0x400) {
                actual_compressed_size = compressed_size;
            } else {
                actual_compressed_size = *(uint16_t *)*s;
                *s += 2;
                *s += 4; // Skip 4 bytes of padding/unknown data
            }

            uint8_t *compressed_data = *s;
            *s += actual_compressed_size;

            bitmap_data = xmalloc(bmp_width * bmp_height * bytes_per_row);
            int success = bitmap_decompress(bitmap_data, bmp_width, bmp_height, compressed_data, actual_compressed_size, bytes_per_row);
            
            if (success) {
                ui_paint_bitmap(left, top, width, height, bmp_width, bmp_height, bitmap_data);
            } else {
                logger(5, 2, "Failed to decompress bitmap");
            }
            xfree(bitmap_data);
        }
    }
}