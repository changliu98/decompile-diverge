void process_bitmap_updates(uint8_t **s) {
    logger(4, 0, "Processing bitmap updates\n");
    
    uint16_t num_updates = *(uint16_t*)*s;
    *s += 2;
    
    for (int i = 0; i < num_updates; i++) {
        uint16_t left = *(uint16_t*)*s;
        *s += 2;
        uint16_t top = *(uint16_t*)*s;
        *s += 2;
        uint16_t right = *(uint16_t*)*s;
        *s += 2;
        uint16_t bottom = *(uint16_t*)*s;
        *s += 2;
        uint16_t width = *(uint16_t*)*s;
        *s += 2;
        uint16_t height = *(uint16_t*)*s;
        *s += 2;
        uint16_t bpp = *(uint16_t*)*s;
        *s += 2;
        
        uint16_t row_size = (bpp + 7) / 8;
        
        uint16_t compress_type = *(uint16_t*)*s;
        *s += 2;
        uint16_t compressed_size = *(uint16_t*)*s;
        *s += 2;
        
        uint16_t update_width = right - left + 1;
        uint16_t update_height = bottom - top + 1;
        
        logger(5, 0, "Bitmap update: left=%d top=%d right=%d bottom=%d width=%d height=%d bpp=%d\n",
               left, top, right, bottom, width, height, bpp);
        
        uint8_t *bitmap_data;
        
        if (compress_type == 0) {
            bitmap_data = xmalloc(width * height * row_size);
            
            for (int j = 0; j < height; j++) {
                uint8_t *dest = bitmap_data + (height - j - 1) * (width * row_size);
                memcpy(dest, *s, width * row_size);
                *s += width * row_size;
            }
            
            ui_paint_bitmap(left, top, update_width, update_height, width, height, bitmap_data);
            xfree(bitmap_data);
        } else {
            uint16_t actual_compressed_size;
            if (compress_type & 0x400) {
                actual_compressed_size = compressed_size;
            } else {
                actual_compressed_size = *(uint16_t*)*s;
                *s += 2;
                *s += 4; // Skip 4 bytes
            }
            
            uint8_t *compressed_data = *s;
            *s += actual_compressed_size;
            
            bitmap_data = xmalloc(width * height * row_size);
            
            if (bitmap_decompress(bitmap_data, width, height, compressed_data, actual_compressed_size, row_size) != 0) {
                ui_paint_bitmap(left, top, update_width, update_height, width, height, bitmap_data);
            } else {
                logger(5, 2, "Bitmap decompression failed\n");
            }
            
            xfree(bitmap_data);
        }
    }
}