void process_bitmap_updates(uint8_t **s) {
    logger(4, 0, "process_bitmap_updates\n");
    
    uint16_t num_updates = *(uint16_t *)*s;
    *s += 2;
    
    for (int i = 0; i < num_updates; i++) {
        uint16_t left = *(uint16_t *)*s;
        *s += 2;
        uint16_t top = *(uint16_t *)*s;
        *s += 2;
        uint16_t right = *(uint16_t *)*s;
        *s += 2;
        uint16_t bottom = *(uint16_t *)*s;
        *s += 2;
        uint16_t width = *(uint16_t *)*s;
        *s += 2;
        uint16_t height = *(uint16_t *)*s;
        *s += 2;
        uint16_t bpp = *(uint16_t *)*s;
        *s += 2;
        
        uint16_t line_size = (bpp + 7) / 8;
        
        uint16_t flags = *(uint16_t *)*s;
        *s += 2;
        uint16_t compress_type = *(uint16_t *)*s;
        *s += 2;
        
        uint16_t cx = right - left + 1;
        uint16_t cy = bottom - top + 1;
        
        logger(5, 0, "bitmap: left=%d top=%d right=%d bottom=%d width=%d height=%d bpp=%d line_size=%d flags=%d compress_type=%d\n",
               left, top, right, bottom, width, height, bpp, line_size, flags, compress_type);
        
        uint8_t *data;
        
        if (flags == 0) {
            data = xmalloc(width * height * line_size);
            for (int y = 0; y < height; y++) {
                memcpy(data + (height - y - 1) * width * line_size, *s, width * line_size);
                *s += width * line_size;
            }
            ui_paint_bitmap(left, top, cx, cy, width, height, data);
            xfree(data);
        } else {
            uint16_t compressed_size;
            if (flags & 0x400) {
                compressed_size = compress_type;
            } else {
                compressed_size = *(uint16_t *)*s;
                *s += 2;
                *s += 4; // Skip 4 bytes
            }
            
            uint8_t *compressed_data = *s;
            *s += compressed_size;
            
            data = xmalloc(width * height * line_size);
            if (bitmap_decompress(data, width, height, compressed_data, compressed_size, line_size)) {
                ui_paint_bitmap(left, top, cx, cy, width, height, data);
            } else {
                logger(5, 2, "bitmap_decompress failed\n");
            }
            xfree(data);
        }
    }
}