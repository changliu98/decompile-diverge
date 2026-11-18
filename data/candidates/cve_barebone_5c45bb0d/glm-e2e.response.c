void process_bitmap_updates(uint8_t **s) {
    uint16_t num_updates = *(uint16_t *)*s;
    *s += 2;

    logger(4, 0, "%s: %d", "process_bitmap_updates", "num_updates");

    for (int i = 0; i < num_updates; i++) {
        uint16_t left = *(uint16_t *)*s;       *s += 2;
        uint16_t top = *(uint16_t *)*s;        *s += 2;
        uint16_t right = *(uint16_t *)*s;      *s += 2;
        uint16_t bottom = *(uint16_t *)*s;     *s += 2;
        uint16_t width = *(uint16_t *)*s;      *s += 2;
        uint16_t height = *(uint16_t *)*s;     *s += 2;
        uint16_t bpp = *(uint16_t *)*s;        *s += 2;
        uint16_t line_size = (bpp + 7) / 8;
        uint16_t flags = *(uint16_t *)*s;      *s += 2;
        uint16_t src_bytes = *(uint16_t *)*s;  *s += 2;

        uint16_t cw = right - left + 1;
        uint16_t ch = bottom - top + 1;

        logger(5, 0, "l=%d t=%d r=%d b=%d w=%d h=%d bpp=%d line=%d flags=%d src_bytes=%d",
               left, top, right, bottom, width, height, bpp, line_size, flags, src_bytes);

        uint8_t *data;

        if (flags == 0) {
            // Uncompressed path
            data = xmalloc(width * height * line_size);
            for (int y = 0; y < height; y++) {
                // Bitmap data is stored bottom-up
                memcpy(data + (height - y - 1) * width * line_size, *s, width * line_size);
                *s += width * line_size;
            }
            ui_paint_bitmap(left, top, cw, ch, width, height, data);
            xfree(data);
        } else {
            // Compressed path
            uint16_t compressed_size;
            if (flags & 0x400) {
                compressed_size = src_bytes;
            } else {
                compressed_size = *(uint16_t *)*s; *s += 2;
                *s += 4; // Skip 4 bytes of unknown/padding data
            }

            uint8_t *input = *s;
            *s += compressed_size;

            data = xmalloc(width * height * line_size);
            int success = bitmap_decompress(data, width, height, input, compressed_size, line_size);
            
            if (success) {
                ui_paint_bitmap(left, top, cw, ch, width, height, data);
            } else {
                logger(5, 2, "process_bitmap_updates: bitmap_decompress failed");
            }
            xfree(data);
        }
    }
}