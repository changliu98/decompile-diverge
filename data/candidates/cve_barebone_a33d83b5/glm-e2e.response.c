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
        
        // Calculate row size: (bpp + 7) / 8 * width
        uint16_t row_size = ((bpp + 7) / 8) * width;
        
        uint16_t flags = *(uint16_t*)*s;
        *s += 2;
        uint16_t compressed_size = *(uint16_t*)*s;
        *s += 2;
        
        uint16_t bitmap_width = right - left + 1;
        uint16_t bitmap_height = bottom - top + 1;
        
        logger(5, 0, "Bitmap: left=%d top=%d right=%d bottom=%d width=%d height=%d bpp=%d row_size=%d flags=%d compressed_size=%d\n",
               left, top, right, bottom, width, height, bpp, row_size, flags, compressed_size);
        
        uint8_t *bitmap_data;
        
        if (flags == 0) {
            // Uncompressed bitmap
            bitmap_data = xmalloc(width * height * row_size);
            
            for (int j = 0; j < height; j++) {
                // Bitmaps are typically stored bottom-up
                uint8_t *dest = bitmap_data + (height - j - 1) * (width * row_size);
                memcpy(dest, *s, width * row_size);
                *s += width * row_size;
            }
            
            ui_paint_bitmap(left, top, bitmap_width, bitmap_height, width, height, bitmap_data);
            xfree(bitmap_data);
        } else {
            // Compressed bitmap
            uint16_t actual_compressed_size;
            
            if (flags & 0x400) {
                actual_compressed_size = compressed_size;
            } else {
                actual_compressed_size = *(uint16_t*)*s;
                *s += 2;
                *s += 4; // Skip 4 bytes of padding/unknown
            }
            
            uint8_t *compressed_data = *s;
            *s += actual_compressed_size;
            
            bitmap_data = xmalloc(width * height * row_size);
            
            if (bitmap_decompress(bitmap_data, width, height, compressed_data, actual_compressed_size, row_size)) {
                ui_paint_bitmap(left, top, bitmap_width, bitmap_height, width, height, bitmap_data);
            } else {
                logger(5, 2, "Bitmap decompression failed\n");
            }
            
            xfree(bitmap_data);
        }
    }
}